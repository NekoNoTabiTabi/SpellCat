#include "Battle.h"
#include <iostream>





Battle::Battle(Player& p, Enemy& e, Deck& d, Dictionary& dictRef, GameState& gState, int f)
    : player(p), enemy(e), deck(d), dict(dictRef), gState(gState), floorNumber(f), hand() 
{
    // initial draw
    for (int i = 0; i < handLimit && !deck.deck.empty(); i++) {
        hand.Add(deck.Draw());
        std::cout << "Drawn: " << hand.hand[i].name << "\n";
    }
    hand.LayoutHand(hand.hand);
    enemy.PlanTurn(enemy);
}

void Battle::HandleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        // select/deselect cards
        for (Card& card : hand.hand) {
            if (CheckCollisionPointRec(mousePos, card.cardBounds)) {
                if (!card.selected) {
                    card.selected = true;
                    hand.wordBuffer.push_back(card);
                }
                else {
                    card.selected = false;
                    hand.wordBuffer.erase(
                        std::remove_if(hand.wordBuffer.begin(), hand.wordBuffer.end(),
                            [&](const Card& c) { return c.id == card.id; }),
                        hand.wordBuffer.end()
                    );
                }
            }
        }

        // confirm button
        if (CheckCollisionPointRec(mousePos, confirmBtn)) {
            ResolvePlayerAttack();
        }
    }
}

void Battle::ResolvePlayerAttack() {
    std::string currentWord;
    for (Card& c : hand.wordBuffer) currentWord += c.name;

      if (!currentWord.empty()) {
        int damage = player.CalculateDamage(hand.wordBuffer, dict.IsValidWord(currentWord));
        int defense = player.CalculateDefense(hand.wordBuffer, dict.IsValidWord(currentWord));
        enemy.hp -= damage;

        // discard used cards
        for (Card& c : hand.wordBuffer) {
            auto it = std::find_if(hand.hand.begin(), hand.hand.end(),
                [&](const Card& h) { return h.id == c.id; });
            if (it != hand.hand.end()) {
                Card discarded = *it;
                discarded.selected = false;
                hand.discardPile.push_back(discarded);
                hand.hand.erase(it);
            }
        }
        hand.wordBuffer.clear();

        hand.LayoutHand(hand.hand);

        if (deck.deck.empty() && !hand.discardPile.empty()) {
            deck.deck = hand.discardPile;
            hand.discardPile.clear();
            deck.Shuffle();
        }

        // enemy turn
        if (enemy.hp > 0) {
            enemy.TakeTurn(enemy, player.hp, defense);
            enemy.PlanTurn(enemy);
        }
    }
}

void Battle::Update() {
    HandleInput();

    if (hand.hand.size() < handLimit) {
        //  initial draw
        int cardsToDraw = handLimit - hand.hand.size();
        hand.DrawingCardsFromDeck(deck, cardsToDraw);
    }

    if (enemy.hp <= 0) {
        // Enemy defeated → switch to reward
        gState = GameState::REWARD;
    }
    else if (player.hp <= 0) {
        // Player lost → switch to defeat
        gState = GameState::DEFEAT;
    }
}

void Battle::Draw() {
    BeginDrawing();
    ClearBackground(GRAY);
    
    int TextScale = ((SCREEN_HEIGHT*2)+ (SCREEN_WIDTH*2))*0.00625;
    //Confirm Butto
    DrawRectangleRec(confirmBtn, !hand.wordBuffer.empty() ? GREEN: DARKGREEN);
    DrawRectangleLinesEx(confirmBtn, 2, BLACK);
    DrawText("CONFIRM", confirmBtn.x + (confirmBtn.width / 2 - (confirmBtn.width * 0.30)), confirmBtn.y + (confirmBtn.height / 2 - (confirmBtn.height * 0.20f)), (((confirmBtn.height * 2) + (confirmBtn.width * 2))*0.05f), WHITE);

    //Player Hp Bar
    int scale = 7;
    Rectangle playerTextureSource = {0,0,32,32};
    Rectangle playerDestinationSource = { SCREEN_WIDTH * 0.20,SCREEN_HEIGHT * 0.25,playerTextureSource.width*scale,playerTextureSource.height * scale };
    DrawText(("Player Health: " + std::to_string(player.hp)).c_str(), SCREEN_WIDTH*0.20 , SCREEN_HEIGHT*0.50, TextScale, BLACK);
    DrawTexturePro(player.sprite, playerTextureSource, playerDestinationSource, {0,0},0,WHITE);
    //Enemy Hp BAR
   
    
    //Enemy Plan, Note: plan to be relative to where enemy sprite is
    Rectangle enemyTextureSource = { 0,0,32,32 };
    Rectangle enemyDestinationSource = { SCREEN_WIDTH * 0.60,SCREEN_HEIGHT * 0.25,enemyTextureSource.width * scale,enemyTextureSource.height * scale };
    DrawText(("Enemy plans to deal " + std::to_string(enemy.damage) + " dmg").c_str(),SCREEN_WIDTH * 0.65, 80, TextScale, MAROON);
    DrawText((enemy.name + " (HP: " + std::to_string(enemy.hp) + ")").c_str(), enemyDestinationSource.x, enemyDestinationSource.y+20, TextScale, RED);
    DrawTexturePro(enemy.sprite, enemyTextureSource, enemyDestinationSource, { 0,0 }, 0, WHITE);
    //Deck and Discard Pile Note: may be Replaced with buttons to allow deck preview or see what's left inside
    DrawText(("Deck: " + std::to_string(deck.deck.size())).c_str(),
        confirmBtn.x, confirmBtn.y-50, TextScale, BLACK);
    DrawText(("Discard: " + std::to_string(hand.discardPile.size())).c_str(),
        confirmBtn.x, confirmBtn.y-25, TextScale, DARKGRAY);
    
    //Floor Text
    DrawText(("Floor: " + std::to_string(floorNumber)).c_str(),
        (SCREEN_WIDTH/2.25), SCREEN_HEIGHT*0.05, TextScale+10, DARKBLUE);


    //WORD PREVIEW
    std::string currentWord;
    for (Card& c : hand.wordBuffer) currentWord += c.name;
    DrawText(( currentWord).c_str(), (SCREEN_WIDTH / 2.50), SCREEN_HEIGHT * 0.60f, TextScale + 30, DARKBLUE);
    //IS VAlid?
    if (!dict.IsValidWord(currentWord) && !currentWord.empty()) {
        DrawText("Not a valid word!", (SCREEN_WIDTH / 2.75), SCREEN_HEIGHT * 0.55f, TextScale + 20, RED);
    }
    //damage an def Calc
    if (!hand.wordBuffer.empty()) {
        int dmgPreview = player.CalculateDamage(hand.wordBuffer, dict.IsValidWord(currentWord));
        DrawText(("Damage: " + std::to_string(dmgPreview)).c_str(), SCREEN_WIDTH * 0.05, SCREEN_HEIGHT * 0.65f, TextScale, RED);
        int defPreview = player.CalculateDefense(hand.wordBuffer, dict.IsValidWord(currentWord));
        DrawText(("Defense: " + std::to_string(defPreview)).c_str(), SCREEN_WIDTH * 0.05, SCREEN_HEIGHT * 0.62f, TextScale, BLUE);
    }
    //HAND
    hand.DrawHand(SCREEN_WIDTH*0.05, SCREEN_HEIGHT*0.70f);

    EndDrawing();
}
void Battle::EndBattle() {
    // Move remaining hand cards into discard pile 
    for (auto& c : hand.hand) {
      
        std::cout << "Put Backed:" << c.name << "/n";
        hand.discardPile.push_back(c);
    }
    hand.hand.clear();

    // Move word buffer too just in case
    for (auto& c : hand.wordBuffer) {
        hand.discardPile.push_back(c);
    }
    hand.wordBuffer.clear();

    // Shuffle discard back into deck
    if (!hand.discardPile.empty()) {
        for (auto& c : hand.discardPile) {
            deck.deck.push_back(c);
        }
        hand.discardPile.clear();
        deck.Shuffle();
    }
}
