#pragma once
#include <raylib.h>
#include <string>
#include "GameState.h"
#include "Card.h"
#include <vector>
#include "Deck.h"
class RewardScreen {
public:
    std::vector<Card> rewardOptions;
    bool skipped = false;
    bool rewardChosen = false;
    Card chosenCard;
    RewardScreen() {
        GenerateRewards();
    }
    ~RewardScreen() = default; //deconstructor

    void Update();
    void Draw();
    void GenerateRewards();
};

