#pragma once
#include <raylib.h>
#include <string>
#include "GameState.h"

class RewardScreen {
public:

    bool skipped = false;
    bool rewardChosen = false;
    std::string chosenCard;
  
    ~RewardScreen() = default; //deconstructor

    void Update();
    void Draw();
};

