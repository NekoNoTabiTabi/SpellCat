#include <raylib.h>
#include "Battle.h"
#include "Player.h"
#include "Enemy.h"
#include "Deck.h"
#include "Dictionary.h"

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

    Battle battle(player, enemy, playerDeck, dict);

    while (!WindowShouldClose()) {
        battle.Update();
        battle.Draw();
    }

    CloseWindow();
}