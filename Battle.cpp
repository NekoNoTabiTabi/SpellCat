#include "Battle.h"
#include <iostream>

Battle::Battle(Player& p, Enemy& e, Deck& d, Dictionary& dictRef,GameState& gState)
    : player(p), enemy(e), deck(d), dict(dictRef), gState(gState) {
    // initial draw
    for (int i = 0; i < handLimit && !deck.deck.empty(); i++) {
        hand.Add(deck.Draw());
    }
    hand.LayoutHand(hand.hand);
    enemy.PlanTurn();
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
        int damage = player.CalculateDamage(currentWord, dict.IsValidWord(currentWord));
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
            enemy.TakeTurn(player.hp);
            enemy.PlanTurn();
        }
    }
}

void Battle::Update() {
    HandleInput();

    if (hand.hand.size() < handLimit) {
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

    DrawRectangleRec(confirmBtn, DARKGREEN);
    DrawRectangleLinesEx(confirmBtn, 2, BLACK);
    DrawText("CONFIRM", confirmBtn.x + 20, confirmBtn.y + 15, 20, WHITE);

    DrawText(("Player Health: " + std::to_string(player.hp)).c_str(), 50, 50, 20, BLACK);
    DrawText(("Enemy HP: " + std::to_string(enemy.hp)).c_str(), 800, 50, 20, RED);
    DrawText(("Enemy plans to deal " + std::to_string(enemy.damage) + " dmg").c_str(),
        700, 80, 20, MAROON);
    DrawText(("Deck: " + std::to_string(deck.deck.size())).c_str(),
        50, 190, 20, BLACK);

    DrawText(("Discard: " + std::to_string(hand.discardPile.size())).c_str(),
        50, 130, 20, DARKGRAY);

    std::string currentWord;
    for (Card& c : hand.wordBuffer) currentWord += c.name;

    DrawText(("Word: " + currentWord).c_str(), 50, 100, 30, DARKBLUE);

    if (!dict.IsValidWord(currentWord) && !currentWord.empty()) {
        DrawText("Not a valid word!", 400, 300, 30, RED);
    }

    if (!hand.wordBuffer.empty()) {
        int dmgPreview = player.CalculateDamage(currentWord, dict.IsValidWord(currentWord));
        DrawText(("Word Damage: " + std::to_string(dmgPreview)).c_str(), 50, 350, 20, RED);
    }

    hand.DrawHand(50, 400);

    EndDrawing();
}

