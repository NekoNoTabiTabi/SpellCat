#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Deck.h"
#include "Hand.h"
#include "Dictionary.h"
#include <raylib.h>
#include "GameState.h"

    class Battle {
    public:
        Battle(Player& p, Enemy& e, Deck& d, Dictionary& dict, GameState& gState);

        // Add a move assignment operator to allow reassigning Battle objects
        Battle(Battle&& other) noexcept
            : player(other.player), enemy(other.enemy), deck(other.deck), hand(std::move(other.hand)), dict(other.dict), gState(other.gState),
              confirmBtn(other.confirmBtn), handLimit(other.handLimit)
        {}

        Battle& operator=(Battle&& other) noexcept {
            if (this != &other) {
                
                enemy = other.enemy;
                deck = other.deck;                  
                gState = other.gState;
                confirmBtn = other.confirmBtn;
             
            }
            return *this;
        }

        // Delete copy constructor and copy assignment to avoid accidental copies
        Battle(const Battle&) = delete;
        Battle& operator=(const Battle&) = delete;

        void Update();
        void Draw();

    private:
        Player& player;
        Enemy& enemy;
        Deck& deck;
        Hand hand;
        Dictionary& dict;
        GameState& gState;

        Rectangle confirmBtn = { 800, 500, 150, 50 };
        int handLimit = 8;

        void HandleInput();
        void ResolvePlayerAttack();
    };


