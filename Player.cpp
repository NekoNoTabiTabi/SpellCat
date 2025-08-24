#include "Player.h"

int Player::CalculateDamage(  std::vector<Card> word, bool isValidWord)
{
    int damage = 0;
    int damagecount= 0;
    for (Card& c : word) {
        if (c.type == "Attack") damage += c.value;
        damagecount++;
    }   
    if (!isValidWord) damage /= 2 ;
    else damage += damagecount;
    
    return damage;
}

int Player::CalculateDefense( std::vector<Card> word, bool isValidWord)
 {
    int defense = 0;
    int defcount = 0;
    for (Card& c : word) {
        if (c.type == "Defense") defense += c.value, defcount++;
    }
    if (!isValidWord) defense /= 2;
    else defense += defcount;


    return defense;
}
