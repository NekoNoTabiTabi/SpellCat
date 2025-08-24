#include "Player.h"

int Player::CalculateDamage(const std::string& word, bool isValidWord)
{
    int damage = 0;

    // Rule 1: base damage = word length
    damage += word.length();

    // Rule 2: bonus for longer words
    if (word.length() >= 5) {
        damage += 3;
    }

    // Rule 3: bonus for specific letters
    for (char c : word) {
        if (c == 'K' || c == 'Z' || c == 'X' || c == 'Q') {
            damage += 2; // rare letters hit harder
        }
    }
    
    if (!isValidWord) damage /= 2;

    
    return damage;
}
