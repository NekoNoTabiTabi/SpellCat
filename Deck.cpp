#include "Deck.h"


Card Deck::CreateCard(const std::string& name, const std::string& type, int value)
    {
        Card c;
        c.id = nextId++; 
        c.name = name;
        c.type = type;
        c.value = value;
        c.effect = "temp";
        return c;
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
