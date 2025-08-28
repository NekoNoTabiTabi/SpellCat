#pragma once
#include <raylib.h>
#include <string>
#include "GameState.h"
#include "Card.h"
#include <vector>
#include "Deck.h"
class RewardScreen {
public:
    RewardScreen(Deck& d);
    std::vector<Card> rewardOptions;
    bool skipped = false;
    bool rewardChosen = false;
    Card chosenCard;


    void Update();
    void Draw();
    void GenerateRewards(Deck& deck);
    

private:
    Deck& deck;
    const int SCREEN_WIDTH = GetScreenWidth();
    const int SCREEN_HEIGHT = GetScreenHeight();
};

