#pragma once
#include <string>
class Enemy
{
    public:
	std::string name;
	int hp=10 ;
	std::string type;
	int damage;

	void PlanTurn();
	void TakeTurn(int& playerHp);
};

