#pragma once
#include "Card.h"
class Player
{
public:
	int hp = 20;
	int CalculateDamage( std::vector<Card>, bool isValidWord);
	int CalculateDefense( std::vector<Card>, bool isValidWord);
	Texture2D sprite =LoadTexture("assets\\player_sprite\\cat.png");
};

