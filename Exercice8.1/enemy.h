#pragma once
#include "player.h"
#include "position.h"

class Enemy
{
public:
	Enemy(const int damage);
	Enemy(int damage, Position pos);
	~Enemy() {};

	int enemyDamage = 4;
	int enemyHealth = 20;

	bool CombatSystem(Player* player);

	Position GetPosition() const;

private:
	Position m_EnemyPosition{ 0, 0 };
};