#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Deck.h"
#include "Hand.h"
#include "Dictionary.h"
#include <raylib.h>
#include "GameState.h"
#include "Card.h"


    class Battle {
    public:
        Battle(Player& p, Enemy& e, Deck& d, Dictionary& dict, GameState& gState, int floorNumber);


        Battle(const Battle&) = delete;
        Battle& operator=(const Battle&) = delete;
        Battle(Battle&&) = delete;
        Battle& operator=(Battle&&) = delete;
        
        

       

        // Delete copy constructor and copy assignment to avoid accidental copies
        
      

        void Update();
        void Draw();
        void EndBattle();

    private:
        Player& player;
        Enemy& enemy;
        Deck& deck;
        Hand hand;
        Dictionary& dict;
        GameState& gState;
        int floorNumber;
        Rectangle confirmBtn = { 800, 500, 150, 50 };
        int handLimit = 8;

        void HandleInput();
        void ResolvePlayerAttack();
    };


