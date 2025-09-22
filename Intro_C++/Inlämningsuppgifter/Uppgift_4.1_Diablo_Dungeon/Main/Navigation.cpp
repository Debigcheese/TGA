#include "Navigation.h"
#include "Diablo.h"
#include "WorldMap.h"
#include "Room.h" 
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "Print.h"

#include <vector>
#include <iostream>

using namespace Print;
using namespace Utils;

Navigation::Navigation(WorldMap& aWorldMap, Player& aPlayer)
	: myWorldMap(aWorldMap), myPlayer(aPlayer)
{
	myNav.currentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
	myNav.previousRoom = myNav.currentRoom;

}

void Navigation::UpdateNavigation()
{
	while (true)
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		myNav.currentRoom->PrintEnemies();
		PrintNavigation();

		int navChoice = ReadIntInRange(1, 5);

		if (navChoice == 5)
		{
			break;
		}

		if (!myNav.currentRoom->GetEnemies().empty())
		{
			std::cout << "You try walking to the door but get attacked!\n";
			myNav.currentRoom->PrintEnemies();
			for (Enemy& enemy : myNav.currentRoom->GetEnemies())
			{
				enemy.Attack(myPlayer);
			}
			system("pause");
			break;
		}

		myNav.currentDirection = static_cast<Direction>(navChoice);

		myNav.currentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
		const std::vector<Door>& doors = myNav.currentRoom->GetDoorsConnected();

		bool doorHasLock = false;
		bool doorFound = false;

		for (const Door& door : doors)
		{
			if (door.GetDirectionFrom(myNav.currentRoom->GetRoomId()) == myNav.currentDirection)
			{
				doorFound = true;
				if (door.HasLock())
				{
					doorHasLock = false; // change this later to true + think theres a bug
					break;
				}
			}

			if (doorFound)
			{
				myNav.previousRoom = myNav.currentRoom;
				int nextId = door.GetOtherRoomId(myNav.currentRoom->GetRoomId());
				myPlayer.SetRoomId(nextId);
				myNav.currentRoom = myWorldMap.GetRoomWithId(nextId);
				break;
			}
		}

		if (doorHasLock)
		{
			doorHasLock = false;
			std::cout << "door has a lock";
			system("pause");
			continue;
		}

		if (!doorFound)
		{
			std::cout << "\nThere is no door in that direction.\n";
			system("pause");
			continue;
		}

		std::cout << "\nEntered room: " << myNav.currentRoom->GetRoomName() << "\n";

		system("pause");

	}
}

void Navigation::UpdateMainMenu()
{
	while (true)
	{
		system("cls");
		myPlayer.SetRoomId(myNav.currentRoom->GetRoomId());
		myPlayer.PrintPlayerUI();
		myNav.currentRoom->PrintEnemies();

		bool enemiesNearby = false;
		int max = 4;
		if (myNav.currentRoom->GetEnemies().empty())
		{
			PrintMainMenu(false, false);
		}
		else
		{
			PrintMainMenu(true, false);
			enemiesNearby = true;
		}

		int menuChoice = ReadIntInRange(1, max);

		switch (menuChoice)
		{
		case 1:
		{
			if (enemiesNearby)
			{
				myPlayer.EnterCombat();
				break;
			}
			std::cout << "No monsters in this room...\n";
			std::cout << "Choose another action.\n";
			system("pause");
			break;
		}
		case 2:
		{
			UpdateNavigation();
			break;
		}
		case 3:
		{
			myPlayer.EnterAttributesMenu();
			break;
		}
		case 4:
		{
			std::cout << "Quitting Game...\n";
			system("pause");
			return;
		}
		case 5:
		{
			std::cout << "Should activate cheats\n";
			break;
		}
		}
	}

}

void Navigation::PrintNavigation() const
{
	std::cout
		<< "\n<--- Navigation --->\n"
		<< "1) West\n"
		<< "2) North\n"
		<< "3) East\n"
		<< "4) South\n"
		<< "5) RETURN\n"
		<< "Choice: ";
}

void Navigation::PrintMainMenu(bool aEnemiesExist, bool aShowCheats) const
{
	std::cout
		<< "\n<--- Main Menu --->\n";
	if (aEnemiesExist)
	{
		std::cout
			<< "1) Combat\n";
	}
	else if (!aEnemiesExist)
	{
		std::cout
			<< "1) Combat (No Enemies Nearby)\n";
	}

	std::cout
		<< "2) Navigate\n"
		<< "3) Attributes\n"
		<< "4) Quit Game\n";
	if (aShowCheats)
	{
		std::cout
			<< "5) Cheats\n";
	}

	std::cout
		<< "Choice: ";

}


