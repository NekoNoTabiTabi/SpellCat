#pragma once
#include <string>
enum class EnemyType {
	SLIME,
	GOBLIN,
	WIZARD,
	BOSS
};

class Enemy
{
    public:
	EnemyType type;
	std::string name;
	int hp;
	int attack;
	
	

	 int damage=0;


	 Enemy() : type(EnemyType::SLIME), hp(5), attack(1), name("Slime") {}
	void PlanTurn();
	void TakeTurn(int& playerHp, int defense);
	Enemy GenerateRandomEnemy(int floorNumber);
};

