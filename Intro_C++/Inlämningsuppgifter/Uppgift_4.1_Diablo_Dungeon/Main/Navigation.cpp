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

Navigation::Navigation(WorldMap aWorldMap, Player aPlayer)
	: myWorldMap(aWorldMap), myPlayer(aPlayer)
{
	myNav.currentRoom = myWorldMap.GetRoomWithId(0);
	myNav.previousRoom = myNav.currentRoom;

}

void Navigation::UpdateNavigation()
{
	while (true)
	{
		system("cls");
		myPlayer.SetRoomId(myNav.currentRoom->GetRoomId());
		PrintLocation(myPlayer.GetRoomId());

		PrintNavigation();
		int navChoice = ReadIntInRange(1, 4);
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

void Navigation::PrintNavigation()
{
	std::cout
		<< "\n<--- Navigation --->\n"
		<< "1) West\n"
		<< "2) North\n"
		<< "3) East\n"
		<< "4) South\n"
		<< "Choice: ";
}

void Navigation::PrintLocation(const int aRoomId)
{
	std::cout << "Location: ";
	std::string location = myNav.currentRoom->GetRoomName();
	std::cout << location << "\n";
}


