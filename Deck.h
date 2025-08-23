
#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "Card.cpp"

struct Deck {
   
    std::vector<Card> deck;

    int RemainingCard() const;
    void Shuffle();
    Card Draw();
};
