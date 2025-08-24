#pragma once
#include "Card.h"
class Player
{
public:
	int hp = 20;
	int CalculateDamage(const std::string& word, bool isValidWord);
};

