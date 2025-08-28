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
        const int SCREEN_WIDTH = GetScreenWidth();
        const int SCREEN_HEIGHT = GetScreenHeight();
        Player& player;
        Enemy& enemy;
        Deck& deck;
        Hand hand;
        Dictionary& dict;
        GameState& gState;
        int floorNumber;

        Rectangle confirmBtn = { SCREEN_WIDTH - (SCREEN_WIDTH* 0.20f), SCREEN_HEIGHT *0.8f, SCREEN_WIDTH*0.15f, SCREEN_HEIGHT*0.083f};
        int handLimit = 8;

        void HandleInput();
        void ResolvePlayerAttack();
    };


