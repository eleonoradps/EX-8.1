#pragma once
#include "position.h"

class Trap
{
public:
	Trap(Position positionTrap);
	~Trap() {};

	Position m_TrapPosition{ 0,0 };

	int trapsDamage = 5;
};