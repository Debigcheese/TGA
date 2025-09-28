#include "PlayerController.h"
#include "WorldMap.h"
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "Cheats.h"
#include "Item.h"

#include <vector>
#include <iostream>

using namespace Utils;

PlayerController::PlayerController(WorldMap& aWorldMap, Player& aPlayer)
	: myWorldMap(aWorldMap), myPlayer(aPlayer), currentRoom(nullptr)
{
}

void PlayerController::UpdateAction()
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		currentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
		myPlayer.SetRoomId(currentRoom->GetRoomId());
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();

		bool enemiesNearby = false;
		if (currentRoom->GetEnemies().empty())
		{
			PrintActionMenu(false, true);
		}
		else
		{
			PrintActionMenu(true, true);
			enemiesNearby = true;
		}

		Action actionChoice = static_cast<Action>(ReadIntInRange(
			static_cast<int>(Action::Combat),
			static_cast<int>(Action::Quit)));

		switch (actionChoice)
		{
			case Action::Combat:
			{
				UpdateCombat();
				break;
			}
			case Action::Navigation:
			{
				UpdateNavigation();
				break;
			}
			case Action::LookAround:
			{
				UpdateScavenge();
				break;
			}
			case Action::Inventory:
			{
				UpdateInventory();
				break;
			}
			case Action::Attributes:
			{
				myPlayer.EnterAttributesMenu();
				break;
			}
			case Action::Cheats:
			{
				UpdateCheats();
				break;
			}
			case Action::Quit:
			{
				std::cout << "Quitting Game...\n";
				system("pause");
				return;
			}
		}
	}
}

void PlayerController::UpdateCombat()
{
	if (!myWorldMap.GetRoomWithId(myPlayer.GetRoomId())->DoesEnemiesExist())
	{
		std::cout << "No monsters in this room...\n";
		std::cout << "Choose another action.\n";
		system("pause");
		return;
	}

	while (true && !myPlayer.IsDead())
	{
		std::vector<Enemy>& enemies = currentRoom->GetEnemies();

		if (myPlayer.IsInvalidAttackIndex() || enemies.size() > 1)
		{
			myPlayer.PrintPlayerUI();
			currentRoom->PrintEnemies();
			myPlayer.ChooseTarget();
			system("cls");
		}
		else
		{
			myPlayer.SetTargetIndex(PLAYER_ATTACK_INDEX_ZERO);
		}

		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemiesWithTarget(myPlayer.GetTargetIndex());
		myPlayer.ChooseAttack();
		system("cls");

		myPlayer.Attack();

		system("pause");

		if (enemies[myPlayer.GetTargetIndex()].IsDead())
		{
			std::cout << "\n" << enemies[myPlayer.GetTargetIndex()].GetName() << " has been slained!\n";
			system("pause");
		}

		system("cls");
		myPlayer.PrintPlayerUI();

		if (enemies[myPlayer.GetTargetIndex()].IsDead())
		{
			currentRoom->RemoveEnemyFromRoom(enemies[myPlayer.GetTargetIndex()].GetId());
			enemies = currentRoom->GetEnemies();
			myPlayer.SetTargetIndex(PLAYER_ATTACK_INDEX_INVALID);
			currentRoom->PrintEnemies();
		}
		else
		{
			currentRoom->PrintEnemiesWithTarget(myPlayer.GetTargetIndex());
		}

		if (enemies.empty())
		{
			std::cout << "\nYou have slain all enemies in this room!\n";
			system("pause");
			break;
		}

		std::cout << "\n";
		for (Enemy& enemy : enemies)
		{
			enemy.Attack(myPlayer);
		}
		system("pause");
	}
}

void PlayerController::UpdateNavigation()
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();
		PrintNavigation();

		int navChoice = ReadIntInRange(
			static_cast<int>(Direction::West),
			static_cast<int>(Direction::South) +
			NAV_DIRECTION_CHOICE_OFFSET);

		if (navChoice == static_cast<int>(Direction::South) + NAV_DIRECTION_CHOICE_OFFSET)
		{
			break;
		}

		if (!currentRoom->GetEnemies().empty() && !Cheats::GetCheats().ghost)
		{
			std::cout << "You try walking to the door but get attacked!\n\n";
			for (Enemy& enemy : currentRoom->GetEnemies())
			{
				enemy.Attack(myPlayer);
			}
			system("pause");
			break;
		}

		bool roomFound = false;

		Position lookForPos = myPlayer.GetPosition() + GetPosFromDirection(static_cast<Direction>(navChoice));
		Room* lookForRoom = nullptr;

		for (Room& room : myWorldMap.GetRooms())
		{
			if (lookForPos == room.GetPosition()) // find room position in direction we want to go
			{
				roomFound = true;
				lookForRoom = &room;
			}
		}

		if (!roomFound)
		{
			std::cout << "\nThere is no door in that direction.\n";
			system("pause");
			continue;
		}

		bool doorHasLock = false;
		bool doorFound = false;

		for (Door& door : myWorldMap.GetDoors())
		{
			if (door.HasMatchingRoomIds(
				lookForRoom->GetRoomId(),
				currentRoom->GetRoomId())) // does door exist between my room and look for room
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
				currentRoom = myWorldMap.GetRoomWithId(lookForRoom->GetRoomId());
				break;
			}
		}

		if (doorHasLock)
		{
			system("pause");
			continue;
		}

		std::cout << "\nEntered room: " << currentRoom->GetRoomName() << "\n";

		if (myPlayer.GetRoomId() == ROOM_WIN_ID)
		{
			Win();
		}

		system("pause");
		break;
	}
}

void PlayerController::UpdateScavenge()
{
	if (!currentRoom->GetEnemies().empty() && !Cheats::GetCheats().ghost)
	{
		std::cout << "You try walking to the door but get attacked!\n\n";
		for (Enemy& enemy : currentRoom->GetEnemies())
		{
			enemy.Attack(myPlayer);
		}
		system("pause");
		//break;
	}

	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();

		bool enemiesNearby = (!currentRoom->GetEnemies().empty() && !Cheats::GetCheats().ghost);

		PrintScavenge();

		Scavenge menuChoice = static_cast<Scavenge>(ReadIntInRange(
			static_cast<int>(Scavenge::Floor),
			static_cast<int>(Scavenge::Return)));

		switch (menuChoice)
		{
			case Scavenge::Floor:
			{
				UpdatePickupItem(myWorldMap.GetRoomWithId(myPlayer.GetRoomId())->GetLootInRoom());
				break;
			}
			case Scavenge::Chests:
			{
				UpdateLootChests();
				break;
			}
			case Scavenge::Spells:
			{
				//UpdateLootChests(); spells
				break;
			}
			case Scavenge::Return:
			{
				return;
			}
		}
	}
}

void PlayerController::UpdatePickupItem(std::vector<Item>& aItems) const
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();

		PrintPickupMenu(aItems);
		if (aItems.empty())
		{
			std::cout << "\n(No loot here...)\n";
			system("pause");
			return;
		}

		const int CHEST_COUNT = static_cast<int>(aItems.size());
		const int RETURN_INDEX = CHEST_COUNT + 1;

		int menuChoice = ReadIntInRange(1, RETURN_INDEX);

		if (menuChoice == RETURN_INDEX)
		{
			return;
		}

		const int CHEST_INDEX = menuChoice - 1;

		Item& itemToPickup = aItems[CHEST_INDEX];

		if (!myPlayer.CanPickupItem(itemToPickup))
		{
			std::cout << "\n(Item too heavy to pickup)\n";
			system("pause");
		}
		else
		{
			myPlayer.AddItemToInventory(itemToPickup);
			std::cout << "\n[" << itemToPickup.GetName() << "]"
				<< " has been added to your inventory!\n";
			currentRoom->GetLootInRoom().erase(currentRoom->GetLootInRoom().begin() + CHEST_INDEX);
			system("pause");
		}
	}
}

//its 01:46 rn and when I first made this fucntion 10min ago
//it looked like crap but then I discovered what
//guard clausing is and it changed my life foerver.
// i will try to guard clause and refactor everything else as much as possible
//so i and u teachers can have an easier time looking through the code(:

void PlayerController::UpdateLootChests() const
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();
		PrintChestMenu();

		auto& chests = currentRoom->GetChestInRoom();

		if (chests.empty())
		{
			std::cout << "\n(No chests here...)\n";
			system("pause");
			return;
		}

		const int CHEST_COUNT = static_cast<int>(chests.size());
		const int RETURN_INDEX = CHEST_COUNT + 1;

		int menuChoice = ReadIntInRange(1, RETURN_INDEX);

		if (menuChoice == RETURN_INDEX)
		{
			return;
		}

		const int CHEST_INDEX = menuChoice - 1;
		Chest& chest = chests[CHEST_INDEX];
		if (chest.GetIsOpen())
		{
			std::cout << "\n(Chest already open)\n";
			system("pause");
			return;
		}

		const auto loot = chest.Open(); //returns items & empties chest

		if (loot.empty())
		{
			std::cout << "\n|" << chest.GetName() << "|"
				<< " has been opened but it was empty...\n";
			system("pause");
			return;
		}

		for (const auto& item : loot)
		{
			currentRoom->AddItemToRoom(item);
		}
		std::cout << "\n|" << chest.GetName() << "|"
			<< " has been opened and dropped items on the floor!\n";

		chests.erase(currentRoom->GetChestInRoom().begin() + CHEST_INDEX);
		system("pause");
		return;
	}
}

void PlayerController::UpdateInventory()
{
}

void PlayerController::Win() const
{
	std::cout << "\nYou reached the last room (" << myPlayer.GetName() << ")!\n";
	std::cout << "Closing game...\n";
	system("pause");
	myPlayer.SetIsDead(true);
	return;
}

void PlayerController::PrintNavigation() const
{
	std::cout
		<< "\n<--- PlayerController --->\n"
		<< "1) West\n"
		<< "2) North\n"
		<< "3) East\n"
		<< "4) South\n\n"
		<< "5) Return\n"
		<< "Choice: ";
}

void PlayerController::PrintActionMenu(bool aEnemiesExist, bool aShowCheats) const
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
		<< "3) Scavenge\n"
		<< "4) Inventory\n";
	std::cout
		<< "\n<--- Other --->\n"
		<< "5) Attributes\n";

	if (aShowCheats)
	{
		std::cout
			<< "6) Cheats\n";
	}

	std::cout
		<< "7) Quit Game\n"
		<< "Choice: ";
}

void PlayerController::PrintScavenge() const
{
	std::cout
		<< "\n<--- Scavenge --->\n"
		<< "1) Floor\n"
		<< "2) Chests\n"
		<< "3) Spells\n"
		<< "4) Return\n"
		<< "Choice: ";
}

void PlayerController::PrintPickupMenu(const std::vector<Item>& aLoot) const
{
	std::cout
		<< "\n<--- Pickup --->\n";
	if (aLoot.empty())
	{
		return;
	}

	for (int i = 0; i < static_cast<int>(aLoot.size()); ++i)
	{
		std::cout << (i + 1) << ") "
			<< "[" << aLoot[i].GetName() << "]" << "\n";
	}

	std::cout << static_cast<int>(aLoot.size()) + 1 << ") Return\n"
		<< "Choice: ";
}

void PlayerController::PrintChestMenu() const
{
	std::cout
		<< "\n<--- Open Chest --->\n";
	if (currentRoom->GetChestInRoom().empty())
	{
		return;
	}

	for (int i = 0; i < static_cast<int>(currentRoom->GetChestInRoom().size()); ++i)
	{
		std::cout << (i + 1) << ") "
			<< "[" << currentRoom->GetChestInRoom()[i].GetName() << "]" << "\n";
	}

	std::cout << static_cast<int>(currentRoom->GetChestInRoom().size()) + 1 << ") Return\n"
		<< "Choice: ";
}
