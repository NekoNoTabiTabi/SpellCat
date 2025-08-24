#include "Enemy.h"
#include <raylib.h>
#include <iostream>
void Enemy::PlanTurn()
{
    damage = GetRandomValue(1, 3);
}
void Enemy::TakeTurn(int& playerHp) 
{
 
    std::cout << "Enemy deals: " << damage<<"\n";
    playerHp -= damage;
    if (playerHp < 0) playerHp = 0;

}
