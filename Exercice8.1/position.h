#pragma once
#include <iostream>

struct Position
{
	int x;
	int y;

	bool operator == (const Position& pos) const
	{
		return x == pos.x && y == pos.y;
	}

	void Print() const
	{
		std::cout << "(" << x << ", " << y << ")\n";
	}
};

static Position wrong_position{ -1, -1 };