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
//random comment do remo ve
int main() {
   const int SCREEN_WIDTH= 1200;
   const int SCREEN_HEIGTH = 800;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGTH, "Spell Cat");

    Dictionary dict;
    dict.LoadDictionary("assets\\words.txt");;

    Player player;
    player.hp = 10;

    Enemy enemy;
    enemy.hp = 1;

    Deck playerDeck;
    playerDeck.deck.push_back(playerDeck.CreateCard("S", "Attack",  1));
    playerDeck.deck.push_back(playerDeck.CreateCard("A", "Attack",  1));
    playerDeck.deck.push_back(playerDeck.CreateCard("T", "Attack",  1));
    playerDeck.deck.push_back(playerDeck.CreateCard("R", "Attack",  1));
    playerDeck.deck.push_back(playerDeck.CreateCard("I", "Attack",  1));
    playerDeck.deck.push_back(playerDeck.CreateCard("K", "Attack",  1));
    playerDeck.deck.push_back(playerDeck.CreateCard("E", "Attack",  1));
    playerDeck.deck.push_back(playerDeck.CreateCard("S", "Defense", 1));
    playerDeck.deck.push_back(playerDeck.CreateCard("A", "Defense", 1));
    playerDeck.deck.push_back(playerDeck.CreateCard("T", "Defense", 1));
    playerDeck.deck.push_back(playerDeck.CreateCard("R", "Defense", 1));
    playerDeck.deck.push_back(playerDeck.CreateCard("I", "Defense", 1));
    playerDeck.deck.push_back(playerDeck.CreateCard("K", "Defense", 1));
    playerDeck.deck.push_back(playerDeck.CreateCard("E", "Defense", 1));
    playerDeck.Shuffle();


    GameState gameState = GameState::BATTLE;
    std::unique_ptr<Battle> battle = nullptr;
    std::unique_ptr<RewardScreen> rewardScreen = nullptr;
    
    DefeatScreen defeatScreen;
    int floorNumber = 0;

    while (!WindowShouldClose()) {
        
        switch (gameState) {

        case GameState::BATTLE:
            if (!battle) {

                enemy= enemy.GenerateRandomEnemy(floorNumber);
                
                enemy.PlanTurn(enemy);
                floorNumber++;

                
                battle = std::make_unique<Battle>(player, enemy, playerDeck, dict, gameState, floorNumber);
            }
            battle->Update();
            battle->Draw();

            if (enemy.hp <= 0) {
                battle->EndBattle();   
                gameState = GameState::REWARD;
            }
            if (player.hp <= 0) {
                battle->EndBattle();   
                gameState = GameState::DEFEAT;
            }
            break;

            

        case GameState::REWARD:
            if (!rewardScreen)   rewardScreen = std::make_unique<RewardScreen>(playerDeck);

            rewardScreen->Update();
            rewardScreen->Draw();

            

                if (rewardScreen->rewardChosen) {
                    if (!rewardScreen->skipped) {
                        playerDeck.deck.push_back(rewardScreen->chosenCard);
                    }

                    enemy = enemy.GenerateRandomEnemy(floorNumber);
                    enemy.PlanTurn(enemy);
                    floorNumber++;

                    battle = std::make_unique<Battle>(player, enemy, playerDeck, dict, gameState, floorNumber);
                    gameState = GameState::BATTLE;
                    rewardScreen.reset();
                }
            
            break;

        case GameState::DEFEAT:
            defeatScreen.Update();
            defeatScreen.Draw();

            if (defeatScreen.retryChosen) {
                // Reset player
                player.hp = 10;

                // Reset deck (you might want to rebuild it or keep progress)
                playerDeck.deck.clear();
                playerDeck.deck.push_back({ 1, "S", "Attack", "Use in words", 1 });
                playerDeck.deck.push_back({ 2, "A", "Attack", "Use in words", 1 });
                playerDeck.deck.push_back({ 3, "T", "Attack", "Use in words", 1 });
                playerDeck.deck.push_back({ 4, "R", "Attack", "Use in words", 1 });
                playerDeck.deck.push_back({ 5, "I", "Attack", "Use in words", 1 });
                playerDeck.deck.push_back({ 6, "K", "Attack", "Use in words", 1 });
                playerDeck.deck.push_back({ 7, "E", "Attack", "Use in words", 1 });
                playerDeck.deck.push_back({ 8, "O", "Defense", "Use in words", 1 });
                playerDeck.deck.push_back({ 9, "E", "Defense", "Use in words", 1 });
                playerDeck.deck.push_back({ 10, "F", "Defense", "Use in words", 1 });
                playerDeck.deck.push_back({ 11, "A", "Defense", "Use in words", 1 });
                playerDeck.deck.push_back({ 12, "U", "Defense", "Use in words", 1 });
                playerDeck.deck.push_back({ 13, "S", "Defense", "Use in words", 1 });
                playerDeck.deck.push_back({ 14, "E", "Defense", "Use in words", 1 });
                playerDeck.Shuffle();

                // Reset floor
                floorNumber = 1;

                // Spawn new battle
                enemy = enemy.GenerateRandomEnemy(floorNumber);
                enemy.PlanTurn(enemy);
                battle = std::make_unique<Battle>(player, enemy, playerDeck, dict, gameState, floorNumber);

                // Reset defeat screen
                defeatScreen.Reset();

                gameState = GameState::BATTLE;
            }
            break;
            
            ;
        }
        CloseWindow();
    }
}
    
    

  