#include <raylib.h>
#include "Battle.h"
#include "Player.h"
#include "Enemy.h"
#include "Deck.h"
#include "Dictionary.h"
#include "GameState.h"
#include "RewardScreen.h"
#include "DefeatScreen.h"
#include <iostream>
int main() {
    InitWindow(1000, 600, "TempRogueLike");

    Dictionary dict;
    dict.LoadDictionary("words.txt");

    Player player;
    player.hp = 10;

    Enemy enemy;
    enemy.hp = 1;

    Deck playerDeck;
    playerDeck.deck.push_back({ 1, "S", "Attack", "Use in words", 1 });
  //  playerDeck.deck.push_back({ 2, "A", "Attack", "Use in words", 1 });
    playerDeck.deck.push_back({ 3, "T", "Attack", "Use in words", 1 });
    playerDeck.deck.push_back({ 4, "R", "Attack", "Use in words", 1 });
    playerDeck.deck.push_back({ 5, "I", "Attack", "Use in words", 1 });
    playerDeck.deck.push_back({ 6, "K", "Attack", "Use in words", 1 });
    playerDeck.deck.push_back({ 7, "E", "Attack", "Use in words", 1 });
   // playerDeck.deck.push_back({ 8, "D", "Defense", "Use in words", 1 });
   // playerDeck.deck.push_back({ 9, "E", "Defense", "Use in words", 1 });
   // playerDeck.deck.push_back({ 10, "F", "Defense", "Use in words", 1 });
   // playerDeck.deck.push_back({ 11, "E", "Defense", "Use in words", 1 });
   // playerDeck.deck.push_back({ 12, "N", "Defense", "Use in words", 1 });
  //  playerDeck.deck.push_back({ 13, "S", "Defense", "Use in words", 1 });
   // playerDeck.deck.push_back({ 14, "E", "Defense", "Use in words", 1 });
    playerDeck.Shuffle();


    GameState gameState = GameState::BATTLE;
    std::unique_ptr<Battle> battle = nullptr;
    std::unique_ptr<RewardScreen> rewardScreen = nullptr;
    // Move all switch-case scoped objects outside the loop to avoid E0546
    DefeatScreen defeatScreen;


    while (!WindowShouldClose()) {
        
        switch (gameState) {

        case GameState::BATTLE:
            if (!battle) {

                enemy = Enemy();
                enemy.hp = 1;
                enemy.PlanTurn();
                battle = std::make_unique<Battle>(player, enemy, playerDeck, dict, gameState);
            }
            battle->Update();
            battle->Draw();

            if (enemy.hp <= 0) {
                battle->EndBattle();   // ✅ cleanup first
                gameState = GameState::REWARD;
            }
            if (player.hp <= 0) {
                battle->EndBattle();   // ✅ cleanup too
                gameState = GameState::DEFEAT;
            }
            break;

            

        case GameState::REWARD:
            if (!rewardScreen)
                rewardScreen = std::make_unique<RewardScreen>();

            rewardScreen->Update();
            rewardScreen->Draw();

            if (rewardScreen->rewardChosen) {
                if (!rewardScreen->skipped) {
                    playerDeck.deck.push_back(rewardScreen->chosenCard);

                    std::cout << "Deck size after reward: " << playerDeck.deck.size() << std::endl;
                    std::cout << rewardScreen->chosenCard.name;

                }

                // Start new enemy/battle
                enemy = Enemy();
                enemy.hp = 1;
                enemy.PlanTurn();
                std::cout << "Deck size after reward: " << playerDeck.deck.size() << std::endl;
                battle = std::make_unique<Battle>(player, enemy, playerDeck, dict, gameState);
                std::cout << "Deck size after reward: " << playerDeck.deck.size() << std::endl;
                gameState = GameState::BATTLE;
                rewardScreen.reset();


            break;

            case GameState::DEFEAT:
            defeatScreen.Update();
            defeatScreen.Draw();
            break;
            }
            ;
        }
        CloseWindow();
    }
}
    
    

  