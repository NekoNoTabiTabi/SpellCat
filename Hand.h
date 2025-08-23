#pragma once
#include "Card.h"

class Hand
{
    public:
    std::vector<Card> hand;
    std::vector<Card> wordBuffer;


    void Add(Card c) { hand.push_back(c); }
    void Remove(int index) { hand.erase(hand.begin() + index); }
    void DrawCard(Card& c);
    void LayoutHand(std::vector<Card>& hand);
    void DrawHand(int x, int y);

    // Add begin/end for range-based for support
    std::vector<Card>::iterator begin() { return hand.begin(); }
    std::vector<Card>::iterator end() { return hand.end(); }
    std::vector<Card>::const_iterator begin() const { return hand.begin(); }
    std::vector<Card>::const_iterator end() const { return hand.end(); }

private:
    
    
   
};
