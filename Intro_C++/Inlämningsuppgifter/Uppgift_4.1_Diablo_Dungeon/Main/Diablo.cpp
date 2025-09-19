#include "Diablo.h"
#include "WorldMap.h"
#include "Player.h"
#include "Room.h" 
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "Print.h"
#include "Navigation.h"

#include <iostream>

using namespace Print;
using namespace Utils;

Diablo::Diablo()
{
}

void Diablo::RunDiablo()
{
	WorldMap world;
	worldMap = world;
	worldMap.GenerateWorld();

	Player player;

	Navigation navig = Navigation(worldMap, player);
	navig.UpdateNavigation();

	PrintIntro();
	PrintMainMenu();
	int menuChoice = ReadIntInRange(1, 2);

	system("cls");

}

