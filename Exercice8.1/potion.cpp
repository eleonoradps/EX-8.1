#include <iostream>
#include "potion.h"
#include "player.h"
#include "position.h"

Potion::Potion(const Position position)
{
	m_PotionPosition = position;
}

Position Potion::GetPosition() const
{
	return m_PotionPosition;
}