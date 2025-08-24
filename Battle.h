#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Deck.h"
#include "Hand.h"
#include "Dictionary.h"
#include <raylib.h>


    class Battle {
    public:
        Battle(Player& p, Enemy& e, Deck& d, Dictionary& dict);

        void Update();
        void Draw();

    private:
        Player& player;
        Enemy& enemy;
        Deck& deck;
        Hand hand;
        Dictionary& dict;

        Rectangle confirmBtn = { 800, 500, 150, 50 };
        int handLimit = 8;

        void HandleInput();
        void ResolvePlayerAttack();
    };


