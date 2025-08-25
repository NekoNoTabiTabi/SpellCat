#include "Enemy.h"
#include <raylib.h>
#include <iostream>
void Enemy::PlanTurn(Enemy e)
{
    damage = GetRandomValue(0,1 );
    damage += e.attack;
}
void Enemy::TakeTurn(Enemy e, int& playerHp, int defense) 
{
    
    damage -= defense;
    if (damage < 0) damage = 0;


    std::cout << "Enemy deals: " << damage<<"\n";
    
    playerHp -= damage;

    if (playerHp < 0) playerHp = 0;

}

Enemy Enemy::GenerateRandomEnemy(int floorNumber) {
    Enemy e;
    int choice = GetRandomValue(0, 2); // slime, goblin, wizard

    if (choice == 0) {
        e.type = EnemyType::SLIME;
        e.name = "Slime";
        e.hp = 5 + floorNumber * 2;         // scales moderately
        e.attack = 1 + floorNumber / 2;
    }
    else if (choice == 1) {
        e.type = EnemyType::GOBLIN;
        e.name = "Goblin";
        e.hp = 8 + floorNumber * 3;         // stronger scaling
        e.attack = 2 + floorNumber / 2;
    }
    else {
        e.type = EnemyType::WIZARD;
        e.name = "Wizard";
        e.hp = 6 + floorNumber * 4;         // glass cannon but strong later
        e.attack = 3 + floorNumber / 2;
    }

    return e;
}