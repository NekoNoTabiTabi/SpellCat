#include "Deck.h"


int Deck::RemainingCard() const{
 
    int remaining = deck.size();
    return remaining;

}
void Deck::Shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
    
}

Card Deck::Draw()
{
    Card c = deck.back();
    deck.pop_back();
    return c;
}
