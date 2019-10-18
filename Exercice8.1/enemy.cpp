#include <iostream>
#include "enemy.h"
#include "player.h"
#include "position.h"

Enemy::Enemy(const int damage, const Position pos)
{
	enemyDamage = damage;
	m_EnemyPosition = pos;
}

bool Enemy::CombatSystem(Player* player)
{
	int hitEnemy;
	int Y = 1;
	int N = 2;

	std::cout << "You encountered an enemy. \n";

	std::cout << "Hit the enemy ? \n Press 1 for Yes or 2 for No. \n";
	std::cin >> hitEnemy;
	//while ((player->playerHealth <= 0) && (enemyHealth <= 0))
	while (hitEnemy = Y)
	{
		if (hitEnemy == Y)
		{
			enemyHealth = enemyHealth - player->playerDamage;
			std::cout << "Your enemy has now " << enemyHealth << " health points left. \n";

			if (enemyHealth <= 0)
			{
				std::cout << "Congratulations you successfully killed the enemy. \n";
			}
			else if (enemyHealth > 0)
			{
				std::cout << "It is now the enemy's turn. \n";
				player->playerHealth = player->playerHealth - enemyDamage;
				std::cout << "You have now " << player->playerHealth << " health points left. \n";
			}
		}
		else if (hitEnemy == N)
		{
			std::cout << "The enemy attacks you first instead. \n";
			player->playerHealth = player->playerHealth - enemyDamage;
			std::cout << "You have now " << player->playerHealth << " health points left. \n";
		}
		//si joueur meurt return false

		if (player->playerHealth <= 0)
		{
			std::cout << "You were killed by your opponent. \n You lost. \n";
			return false;
		}
		//si enemi meur return true;

		if (enemyHealth <= 0)
		{
			std::cout << "You killed your opponent! \n You won! \n";
			return true;
		}
	}

}

Position Enemy::GetPosition() const
{
	return m_EnemyPosition;
}