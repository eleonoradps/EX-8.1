#include "map.h"
#include <iostream>

#include <random>
#include <time.h>

Map::Map()
{
	std::default_random_engine generator(time(NULL));
	const std::uniform_int_distribution<int> distribution(0, LENGTH - 1);

	int i = 0;
	for (auto& tile : tiles_)
	{
		auto diceRoll = distribution(generator);
		tile = static_cast<Tile>(diceRoll);

		if (IsFree(tile))
		{
			freeTiles_.push_back(i);
		}
		i++;
	}
}

Map::Map(std::vector<std::vector<short>> tiles)
{
	tiles_.resize(tiles.size() * tiles[0].size());

	sizeX_ = tiles[0].size();
	sizeY_ = tiles.size();

	for (auto y = 0; y < tiles.size(); y++)
	{
		for (auto x = 0; x < tiles[y].size(); x++)
		{
			tiles_[Pos2Index(x, y)] = static_cast<Tile>(tiles[y][x]);

			if (IsFree(x, y))
			{
				freeTiles_.push_back(Pos2Index(x, y));
			}
		}
	}
}

Map::~Map() {}

void Map::Print()
{
	auto line = 1;
	std::vector<std::string> result;
	result.reserve(tiles_.size());
	int index = 0;
	for (auto& tile : tiles_)
	{
		if (Pos2Index(player_->GetPosition()) == index)
		{
			auto c = TileToChar(Tile::PLAYER);
			result.insert(result.end(), c.begin(), c.end());
		}
		else {
			bool found = false;
			//Check potion
			for (auto& potion : potions_)
			{
				if (Pos2Index(potion->GetPosition()) == index) {
					auto c = TileToChar(Tile::POTION);
					result.insert(result.end(), c.begin(), c.end());
					found = true;
					break;
				}
			}

			//Check enemies
			if (!found) {
				for (auto& enemy : enemies_)
				{
					//Get position of enemy
					if (Pos2Index(enemy->GetPosition()) == index) {
						auto c = TileToChar(Tile::ENEMY);
						result.insert(result.end(), c.begin(), c.end());
						found = true;
						break;
					}
				}
			}

			//Check traps
			if (!found) {
				for (auto& trap : traps_)
				{
					//Get position of enemy
					if (Pos2Index(trap->m_TrapPosition) == index) {
						auto c = TileToChar(Tile::TRAP);
						result.insert(result.end(), c.begin(), c.end());
						found = true;
						break;
					}
				}
			}

			//Wall
			if (!found) {
				auto c = TileToChar(tile);
				result.insert(result.end(), c.begin(), c.end());
			}
		}


		if (line % sizeX_ == 0)
		{
			result.push_back("\n");
		}

		line++;
		index++;
	}

	for (auto value : result)
	{
		std::cout << value;
	}
}

Position Map::GetRandomPosition()
{
	if (freeTiles_.empty())
	{
		return wrong_position;
	}

	std::default_random_engine generator(time(NULL));
	const std::uniform_int_distribution<int> distribution(0, freeTiles_.size() - 1);
	const auto indexFreeTile = distribution(generator);
	const auto pos = Index2Pos(freeTiles_[indexFreeTile]);

	//Remove free tile
	std::vector<int> newFreeTiles;
	newFreeTiles.reserve(freeTiles_.size() - 1);
	for (auto i = 0; i < freeTiles_.size(); i++)
	{
		if (i != indexFreeTile)
		{
			newFreeTiles.push_back(freeTiles_[i]);
		}
	}
	freeTiles_.clear();
	freeTiles_.assign(newFreeTiles.begin(), newFreeTiles.end());

	return pos;
}

bool Map::IsFree(Position pos) const
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= sizeX_ || pos.y >= sizeY_) return false;

	return tiles_[Pos2Index(pos)] != WALL;
}

bool Map::IsFree(const int x, const int y) const
{
	return IsFree(Position{ x, y });
}

bool Map::IsFree(const Tile tile) const
{
	return tile != WALL;
}

void Map::AddPlayer(Player& player)
{
	player_ = &player;
}

void Map::AddPotion(Potion& potion)
{
	potions_.push_back(&potion);
}

void Map::RemovePotion(Potion& potion)
{
	std::vector<Potion*> newPotions;

	for (int i = 0; i < potions_.size(); i++)
	{
		if (potions_[i] != &potion)
		{
			newPotions.push_back(potions_[i]);
		}
	}

	potions_ = newPotions;
}

void Map::AddEnemy(Enemy& enemy)
{
	enemies_.push_back(&enemy);
}

void Map::RemoveEnemy(Enemy& enemy)
{
	std::vector<Enemy*> newEnemies;

	for (int i = 0; i < enemies_.size(); i++)
	{
		if (enemies_[i] != &enemy)
		{
			newEnemies.push_back(enemies_[i]);
		}
	}

	enemies_ = newEnemies;
}

void Map::AddTrap(Trap& trap)
{
	traps_.push_back(&trap);
}

void Map::Update()
{
	//Check if player is at the same position as a potion
	int indexPotionToRemove = -1;
	for (int i = 0; i < potions_.size(); i++)
	{
		if (potions_[i]->GetPosition() == player_->GetPosition())
		{
			if (player_->PickupPotion(*potions_[i]))
			{
				indexPotionToRemove = i;
			}
		}
	}

	//If a potion has been taken, them remove it from the map
	if (indexPotionToRemove != -1)
	{
		std::vector<Potion*> newPotion;
		for (int i = 0; i < potions_.size(); i++)
		{
			if (i != indexPotionToRemove)
			{
				newPotion.push_back(potions_[i]);
			}
		}

		potions_ = newPotion;
	}

	//Check if player is at the same position as a enemy
	int indexEnemyToRemove = -1;
	for (int i = 0; i < enemies_.size(); i++)
	{
		if (enemies_[i]->GetPosition() == player_->GetPosition())
		{
			if (enemies_[i]->CombatSystem(player_))
			{
				indexEnemyToRemove = i;
			}
		}
	}

	//If an enemy has been killed, then remove it from the map
	if (indexEnemyToRemove != -1)
	{
		std::vector<Enemy*> newEnemies;
		for (auto i = 0; i < enemies_.size(); i++)
		{
			if (i != indexEnemyToRemove)
			{
				newEnemies.push_back(enemies_[i]);
			}
		}
		enemies_ = newEnemies;
	}

	//Check if player is at the same position as a trap
	int indexTrapToRemove = -1;
	for (int i = 0; i < traps_.size(); i++)
	{
		if (traps_[i]->m_TrapPosition == player_->GetPosition())
		{
			if (player_->playerHealth -= traps_[i]->trapsDamage)
			{
				indexTrapToRemove = i;
			}
		}
	}

	//If an enemy has been killed, then remove it from the map
	if (indexTrapToRemove != -1)
	{
		std::vector<Trap*> newTraps;
		for (auto i = 0; i < traps_.size(); i++)
		{
			if (i != indexTrapToRemove)
			{
				newTraps.push_back(traps_[i]);
			}
		}
		traps_ = newTraps;
	}
}

Position Map::Index2Pos(const int index) const
{
	return Position{ index % sizeX_, index / sizeX_ };
}

int Map::Pos2Index(const Position pos) const
{
	return pos.y * sizeX_ + pos.x;
}

int Map::Pos2Index(const int x, const int y) const
{
	return y * sizeX_ + x;
}

std::vector<std::string> Map::TileToChar(const Tile tile)
{
	std::vector<std::string> c;
	switch (tile)
	{
	case WALL:
	{
		c.emplace_back("|");
		break;
	}
	case GROUND:
	{
		c.emplace_back(" ");
		break;
	}
	case PLAYER:
		c.emplace_back("\x1B[31m");
		c.emplace_back("@");
		c.emplace_back("\033[0m");
		break;
	case POTION:
		c.emplace_back("+");
		break;
	case ENEMY:
		c.emplace_back("E");
		break;
	case TRAP:
		c.emplace_back("T");
		break;
	case LENGTH: break;
	default:
	{
		c.emplace_back("X");
	}
	}

	return c;
}
