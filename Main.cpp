#include <raylib.h>
#include "Battle.h"
#include "Player.h"
#include "Enemy.h"
#include "Deck.h"
#include "Dictionary.h"
#include "GameState.h"
#include "RewardScreen.h"
#include "DefeatScreen.h"
int main() {
    InitWindow(1000, 600, "TempRogueLike");

    Dictionary dict;
    dict.LoadDictionary("words.txt");

    Player player;
    player.hp = 10;

    Enemy enemy;
    enemy.hp = 20;

    Deck playerDeck;
    playerDeck.deck.push_back({ 1, "S", "Letter", "Use in words", 1 });
    playerDeck.deck.push_back({ 2, "A", "Letter", "Use in words", 1 });
    playerDeck.deck.push_back({ 3, "T", "Letter", "Use in words", 1 });
    playerDeck.deck.push_back({ 4, "R", "Letter", "Use in words", 1 });
    playerDeck.deck.push_back({ 5, "I", "Letter", "Use in words", 1 });
    playerDeck.deck.push_back({ 6, "K", "Letter", "Use in words", 1 });
    playerDeck.deck.push_back({ 7, "E", "Letter", "Use in words", 1 });
    playerDeck.Shuffle();
    GameState gameState = GameState::BATTLE;
    std::unique_ptr<RewardScreen> rewardScreen = nullptr;
    // Move all switch-case scoped objects outside the loop to avoid E0546
    DefeatScreen defeatScreen;
    Battle battle(player, enemy, playerDeck, dict, gameState);

    while (!WindowShouldClose()) {
        switch (gameState) {

        case GameState::BATTLE:
            battle.Update();
            battle.Draw();
            if (enemy.hp <= 0) gameState = GameState::REWARD;
            if (player.hp <= 0) gameState = GameState::DEFEAT;
            break;

        case GameState::REWARD:
            if (!rewardScreen)
                rewardScreen = std::make_unique<RewardScreen>();

            rewardScreen->Update();
            rewardScreen->Draw();

            if (rewardScreen->rewardChosen) {
                if (rewardScreen->chosenCard == "Heal 5") player.hp += 5;

                enemy = Enemy();
                enemy.hp = 20;
                enemy.PlanTurn();

                battle = Battle(player, enemy, playerDeck, dict, gameState);
                gameState = GameState::BATTLE;

                rewardScreen.reset();  
            }
            break;

        case GameState::DEFEAT:
            defeatScreen.Update();
            defeatScreen.Draw();
            break;
        }
    }

    CloseWindow();
}