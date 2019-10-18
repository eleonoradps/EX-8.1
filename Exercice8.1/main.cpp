#include <iostream>
#include "position.h"
#include "player.h"
#include "potion.h"
#include "map.h"

// ex 7.0
void MapMenu(Player player)
{

	std::cout << "\n ##################################################	\n";
	std::cout << " # \t\t Commands: \t\t\t  # \n";
	std::cout << " # \t\t UP = w \t\t\t  # \n";
	std::cout << " # \t\t DOWN = s \t\t\t  # \n";
	std::cout << " # \t\t LEFT = a      \t\t\t  # \n";
	std::cout << " # \t\t RIGHT = d      \t\t  # \n";
	std::cout << " # \t\t INVENTORY = p      \t\t  # \n";
	std::cout << " # \t\t Player Health : " << player.playerHealth << "      \t  # \n";
	std::cout << " # \t\t       \t\t\t\t  # \n";
	std::cout << " ################################################## \n";


}

int main()
{


	Player player = Player();

	Map map = Map(level_0);
	map.AddPlayer(player);

	Potion p0 = Potion(map.GetRandomPosition());
	Potion p1 = Potion(map.GetRandomPosition());
	Potion p2 = Potion(map.GetRandomPosition());

	map.AddPotion(p0);
	map.AddPotion(p1);
	map.AddPotion(p2);

	Enemy e0 = Enemy(4, map.GetRandomPosition());
	Enemy e1 = Enemy(4, map.GetRandomPosition());
	Enemy e2 = Enemy(4, map.GetRandomPosition());

	map.AddEnemy(e0);
	map.AddEnemy(e1);
	map.AddEnemy(e2);

	Trap trap0 = Trap(map.GetRandomPosition());
	Trap trap1 = Trap(map.GetRandomPosition());
	Trap trap2 = Trap(map.GetRandomPosition());

	map.AddTrap(trap0);
	map.AddTrap(trap1);
	map.AddTrap(trap2);

	//First print
	map.Print();
	MapMenu(player);



	while (player.playerHealth > 0 && (e0.enemyHealth > 0 || e1.enemyHealth > 0 || e2.enemyHealth > 0))
	{
		//move player
		player.MoveSet(&map);

		//Clear and draw new map
		system("cls");
		map.Print();

		MapMenu(player);

		map.Update();
	}
}

