#pragma once
#include <vector>
#include "position.h"
#include "potion.h"

class Map; //Prototype

enum class MoveDirection
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

enum class MoveResult
{
	OK,
	CANNOT_MOVE_FURTHER,
	COLLISION
};


class Player
{
public:
	Player() {};
	void MoveSet(Map* map);
	int playerHealth = 30;
	int playerDamage = 5;

	void PlayerHealth();

	int playerInput{};

	bool PickupPotion(Potion potion);

	Position GetPosition() const;


private:

	Position m_PlayerPosition{ 1, 1 };
	MoveDirection direction;

	const int maxPotion = 5;
	std::vector<Potion> healthPotions;
};
