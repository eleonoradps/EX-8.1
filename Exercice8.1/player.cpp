#include <iostream>
#include <vector>
#include "position.h"
#include "player.h"
#include "map.h"

void Player::MoveSet(Map* map)
{
	char key;
	bool move = true;

	MoveDirection direction = MoveDirection::DOWN;

	MoveResult moveResult = MoveResult::OK;

	std::cin >> key;

	switch (key)
	{
	case 'w':
		direction = MoveDirection::UP;
		break;

	case 'a':
		direction = MoveDirection::LEFT;
		break;

	case 's':
		direction = MoveDirection::DOWN;
		break;

	case 'd':
		direction = MoveDirection::RIGHT;
		break;
	case 'p':
		PlayerHealth();
		return;
		break;
	default:
		direction = MoveDirection::UP;
	}

	//rajouter le IsFree() de la map une fois le merge fait

	switch (moveResult)
	{
	case MoveResult::CANNOT_MOVE_FURTHER:
		move = false;
		std::cout << "You cannot move further. \n Go back. \n";
		break;

	case MoveResult::COLLISION:
		move = false;
		std::cout << "Collision. \n You can't get through. \n";
		break;
	}

	if (!move)
	{
		return;
	}

	switch (direction) {
	case MoveDirection::DOWN:
		m_PlayerPosition.y += 1;
		if (!map->IsFree(m_PlayerPosition))
		{
			m_PlayerPosition.y -= 1;
		}
		break;

	case MoveDirection::UP:
		m_PlayerPosition.y -= 1;
		if (!map->IsFree(m_PlayerPosition))
		{
			m_PlayerPosition.y += 1;
		}
		break;

	case MoveDirection::LEFT:
		m_PlayerPosition.x -= 1;
		if (!map->IsFree(m_PlayerPosition))
		{
			m_PlayerPosition.x += 1;
		}
		break;

	case MoveDirection::RIGHT:
		m_PlayerPosition.x += 1;
		if (!map->IsFree(m_PlayerPosition))
		{
			m_PlayerPosition.x -= 1;
		}
		break;

	}

	m_PlayerPosition.Print();
}

bool Player::PickupPotion(Potion potion)
{
	int y = 1;
	int n = 2;
	std::cout << "PICKUP POTION\n";
	std::cout << "Do you want to pick up the potion ? \n Press 1 for yes or 2 for no \n";
	std::cin >> playerInput;

	if (playerInput == y)
	{
		std::cout << "You picked up a healing potion. \n";
		healthPotions.push_back(potion);
		return true;
	}
	//sinon return false
	else if (playerInput == n)
	{
		playerInput = n;
		return false;
	}
}

void Player::PlayerHealth()
{
	if (healthPotions.empty())
	{
		std::cout << "You don't have any potions. \n";
		return;
	}

	std::cout << "To drink healing potion, press [1]. \n To continue playing, Press [2]. \n";
	std::cin >> playerInput;

	if (playerInput == 1)
	{
		std::cout << "You drank a healing potion. \n";
		playerHealth = playerHealth + healthPotions[healthPotions.size() - 1].healthPotion;

		healthPotions.pop_back();
	}
	else if (playerInput == 2)
	{
		std::cout << "You did not use potion. \n";
		return;
	}
}

Position Player::GetPosition() const
{
	return m_PlayerPosition;
}

