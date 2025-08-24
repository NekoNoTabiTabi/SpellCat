
#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "Card.h"

class Deck {
    public:
    std::vector<Card> deck;

    
    void Shuffle();
    Card Draw();
};
