#include "Navigation.h"
#include "Diablo.h"
#include "WorldMap.h"
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "Cheats.h"

#include <vector>
#include <iostream>

using namespace Utils;

Navigation::Navigation(WorldMap& aWorldMap, Player& aPlayer)
	: myWorldMap(aWorldMap), myPlayer(aPlayer)
{
	myNav.currentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
	myNav.previousRoom = myNav.currentRoom;
}

void Navigation::UpdateNavigation()
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		myNav.currentRoom->PrintEnemies();
		PrintNavigation();

		int navChoice = ReadIntInRange(
			static_cast<int>(Direction::Direction_West),
			static_cast<int>(Direction::Direction_South) +
			NAV_DIRECTION_CHOICE_OFFSET);

		if (navChoice == static_cast<int>(Direction::Direction_South) + NAV_DIRECTION_CHOICE_OFFSET)
		{
			break;
		}

		if (!myNav.currentRoom->GetEnemies().empty() && !Cheats::GetCheats().ghost)
		{
			std::cout << "You try walking to the door but get attacked!\n\n";
			for (Enemy& enemy : myNav.currentRoom->GetEnemies())
			{
				enemy.Attack(myPlayer);
			}
			system("pause");
			break;
		}

		myNav.currentDirection = static_cast<Direction>(navChoice);

		myNav.currentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
		std::vector<Door>& doors = myNav.currentRoom->GetDoorsConnected();

		bool doorHasLock = false;
		bool doorFound = false;

		for (Door& door : doors)
		{
			if (door.GetDirectionFrom(myNav.currentRoom->GetRoomId()) == myNav.currentDirection)
			{
				doorFound = true;
				if (door.HasLock())
				{
					doorHasLock = true;
					door.UpdateDoorLock(myPlayer);
					doorHasLock = door.HasLock();
				}
			}

			if (doorFound && !doorHasLock)
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

		if (myPlayer.GetRoomId() == ROOM_WIN_ID)
		{
			Win();
		}

		system("pause");
		break;
	}
}

void Navigation::UpdateAction()
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.SetRoomId(myNav.currentRoom->GetRoomId());
		myPlayer.PrintPlayerUI();
		myNav.currentRoom->PrintEnemies();

		bool enemiesNearby = false;
		if (myNav.currentRoom->GetEnemies().empty())
		{
			PrintActionMenu(false, true);
		}
		else
		{
			PrintActionMenu(true, true);
			enemiesNearby = true;
		}

		int menuChoice = ReadIntInRange(static_cast<int>(Action::Action_Combat),
		                                static_cast<int>(Action::Action_Cheats));
		Action actionChoice = static_cast<Action>(menuChoice);

		switch (actionChoice)
		{
		case Action::Action_Combat:
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
		case Action::Action_Navigation:
			{
				UpdateNavigation();
				break;
			}
		case Action::Action_Attributes:
			{
				myPlayer.EnterAttributesMenu();
				break;
			}
		case Action::Action_Quit:
			{
				std::cout << "Quitting Game...\n";
				system("pause");
				return;
			}
		case Action::Action_Cheats:
			{
				UpdateCheats();
				break;
			}
		}
	}
}

void Navigation::Win() const
{
	std::cout << "\nYou reached the last room (" << myPlayer.GetName() << ")!\n";
	std::cout << "Closing game...\n";
	system("pause");
	myPlayer.SetIsDead(true);
	return;
}

void Navigation::PrintNavigation() const
{
	std::cout
		<< "\n<--- Navigation --->\n"
		<< "1) West\n"
		<< "2) North\n"
		<< "3) East\n"
		<< "4) South\n\n"
		<< "5) Return\n"
		<< "Choice: ";
}

void Navigation::PrintActionMenu(bool aEnemiesExist, bool aShowCheats) const
{
	std::cout
		<< "\n<--- Action --->\n";
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
