
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
    int nextId = 1;


    Card CreateCard(const std::string& name, const std::string& type, int value);
    void Shuffle();
    Card Draw();
};
