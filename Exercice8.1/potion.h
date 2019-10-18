#pragma once
#include "position.h"

class Player;

class Potion
{
public:
	Potion() {};
	Potion(Position position);
	~Potion() {};
	int healthPotion = 5;

	void Print();

	Position GetPosition() const;

private:
	Position m_PotionPosition{ 0, 0 };
};