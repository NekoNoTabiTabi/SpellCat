#pragma once
#include <string>
#include <raylib.h>
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
	int damage = 0;
	
	Texture2D sprite = LoadTexture("assets\\enemy_sprite\\Slime.png");
	 


	Enemy() : type(EnemyType::SLIME), hp(5), attack(1), name("Slime"),sprite(LoadTexture("assets\\enemy_sprite\\Slime.png")) {}
	void PlanTurn(Enemy e);
	void TakeTurn(Enemy e, int& playerHp, int defense);
	Enemy GenerateRandomEnemy(int floorNumber);
};

