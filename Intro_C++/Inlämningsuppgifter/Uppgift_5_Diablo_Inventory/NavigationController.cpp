#include "NavigationController.h"
#include "Cheats.h"
#include "ConsoleUI.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "WorldMap.h"

#include <iostream>

NavigationController::NavigationController(WorldMap& aWorldMap, Player& aPlayer)
	: myPlayer(aPlayer), myWorldMap(aWorldMap), myCurrentRoom(nullptr)
{
}

void NavigationController::UpdateNavigation(Room* aRoom)
{
	while (true && !myPlayer.IsDead())
	{
		myCurrentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
		ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);
		ConsoleUI::PrintMap(myPlayer.GetPosition(), myWorldMap.GetWinRoomPos());
		ConsoleUI::PrintNavigationMenu();

		int navChoice = Utils::ReadIntInRange(
			static_cast<int>(Direction::West),
			static_cast<int>(Direction::South) +
			NAV_DIRECTION_CHOICE_OFFSET);

		if (navChoice == static_cast<int>(Direction::South) + NAV_DIRECTION_CHOICE_OFFSET)
		{
			return;
		}

		Position lookForPos = myPlayer.GetPosition() + Utils::GetPosFromDirection(static_cast<Direction>(navChoice));
		Room* lookForRoom = GetLookForRoom(lookForPos);

		if (lookForRoom == nullptr)
		{
			std::cout << "\nThere is no door in that direction.\n";
			ConsoleUI::Pause();
			continue;
		}

		if (HandleOnEnemyAggro())
		{
			return;
		}

		bool doorHasLock = false;
		bool doorFound = false;

		for (Door& door : myWorldMap.GetDoors())
		{
			if (door.HasMatchingRoomIds(
				lookForRoom->GetRoomId(),
				myCurrentRoom->GetRoomId())) // does door exist between my room and look for room
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
				myPlayer.SetPosition(lookForRoom->GetPosition());
				myPlayer.SetRoomId(lookForRoom->GetRoomId());
				myCurrentRoom = myWorldMap.GetRoomWithId(lookForRoom->GetRoomId());
				break;
			}
		}

		if (doorHasLock)
		{
			ConsoleUI::Pause();
			continue;
		}

		std::cout << "\nEntered room: " << myCurrentRoom->GetRoomName() << "\n";
		std::cout << "You healed to full hp: " << std::round(myPlayer.GetAttributes().currentHealth)
			<< " -> " << std::round(myPlayer.GetAttributes().maxHealth) << "\n";
		myPlayer.HealFullHealth();

		ConsoleUI::Pause();
		return;
	}
}

Room* NavigationController::GetLookForRoom(const Position& aLookForPos) const
{
	for (Room& room : myWorldMap.GetRooms())
	{
		if (aLookForPos == room.GetPosition()) // find room position in direction we want to go
		{
			return &room;
		}
	}
	return nullptr;
}

bool NavigationController::HandleOnEnemyAggro() const
{
	if (!myCurrentRoom->GetEnemies().empty() && !Cheats::GetCheats().ghost)
	{
		std::cout << "You try walking to the door but get attacked!\n\n";
		for (Enemy& enemy : myCurrentRoom->GetEnemies())
		{
			enemy.Attack(myPlayer);
		}
		ConsoleUI::Pause();
		return true;
	}
	return false;
}
