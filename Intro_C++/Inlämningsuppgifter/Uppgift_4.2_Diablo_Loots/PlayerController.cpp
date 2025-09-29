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
					UpdateAttributes();
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
		std::cout << "You try scavenging the room but get attacked!\n\n";
		for (Enemy& enemy : currentRoom->GetEnemies())
		{
			enemy.Attack(myPlayer);
		}
		system("pause");
		return;
	}
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();

		PrintScavenge();

		Scavenge menuChoice = static_cast<Scavenge>(ReadIntInRange(
			static_cast<int>(Scavenge::Floor),
			static_cast<int>(Scavenge::Return)));

		switch (menuChoice)
		{
			case Scavenge::Floor:
				{
					UpdatePickupItem();
					break;
				}
			case Scavenge::Chests:
				{
					UpdateLootChests();
					break;
				}
			case Scavenge::Spells:
				{
					UpdateReadSpells();
					break;
				}
			case Scavenge::Return:
				{
					return;
				}
		}
	}
}

void PlayerController::UpdatePickupItem() const
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();
		auto& items = currentRoom->GetLootInRoom();

		PrintPickupMenu();
		if (items.empty())
		{
			std::cout << "(No loot here...)\n";
			system("pause");
			return;
		}

		const int CHEST_COUNT = static_cast<int>(items.size());
		const int RETURN_INDEX = CHEST_COUNT + 1;

		int menuChoice = ReadIntInRange(1, RETURN_INDEX);

		if (menuChoice == RETURN_INDEX)
		{
			return;
		}

		const int CHEST_INDEX = menuChoice - 1;

		Item& itemToPickup = items[CHEST_INDEX];

		if (!myPlayer.CanPickupItem(itemToPickup))
		{
			std::cout << "\n(Item too heavy to pickup)\n";
			system("pause");
		}
		else
		{
			myPlayer.AddItemToInventory(itemToPickup);
			std::cout << "\n";
			itemToPickup.PrintItemName();
			std::cout << " has been added to your inventory!\n";
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
			std::cout << "(No chests here...)\n";
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

		//chests.erase(currentRoom->GetChestInRoom().begin() + CHEST_INDEX);
		system("pause");
		return;
	}
}

void PlayerController::UpdateReadSpells() const
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();
		auto& spells = currentRoom->GetSpellsInRoom();
		PrintSpells();

		if (spells.empty())
		{
			std::cout << "(No spells here...)\n";
			system("pause");
			return;
		}

		const int SPELLS_COUNT = static_cast<int>(spells.size());
		const int RETURN_INDEX = SPELLS_COUNT + 1;
		int menuChoice = ReadIntInRange(1, RETURN_INDEX);

		if (menuChoice == RETURN_INDEX)
		{
			return;
		}

		const int SPELL_INDEX = menuChoice - 1;
		Spell& spell = spells[SPELL_INDEX];

		myPlayer.ApplySpell(spell);
		std::cout << "\n";
		spell.PrintSpellName();
		std::cout << " spell buff has been applied!\n";
		spells.erase(spells.begin() + SPELL_INDEX);
		system("pause");
	}
}

void PlayerController::UpdateInventory() const
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();

		myPlayer.PrintInventory();

		const int OFFSET_INDEX = 1;
		const int RETURN_INDEX = static_cast<int>(myPlayer.GetInventory().size()) + OFFSET_INDEX;

		int menuChoice = ReadIntInRange(OFFSET_INDEX, RETURN_INDEX);

		if (menuChoice == RETURN_INDEX)
		{
			return;
		}

		const int ITEM_INDEX = menuChoice - OFFSET_INDEX;
		Item item = myPlayer.GetInventory()[ITEM_INDEX];

		std::cout << "\nDrop item?\n"
			<< "1) Yes\n"
			<< "2) No\n"
			<< "Choice: ";

		int dropItemChoice = ReadIntInRange(1, 2);

		if (dropItemChoice == 2)
		{
			return;
		}
		currentRoom->AddItemToRoom(item);
		myPlayer.RemoveFromInventory(ITEM_INDEX);

		std::cout << "\nYou dropped ";
		item.PrintItemName();
		std::cout << " on the floor\n";
		system("pause");
		return;
	}
}

void PlayerController::UpdateAttributes() const
{
	while (true)
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();

		std::cout
			<< "\n<--- Attributes --->\n"
			<< "1) Starting Attributes\n"
			<< "2) Buffed Attributes\n"
			<< "3) Return\n"
			<< "Choice: ";

		AttriMenu menuChoice = static_cast<AttriMenu>(ReadIntInRange(
			static_cast<int>(AttriMenu::Attributes),
			static_cast<int>(AttriMenu::Return)));

		if (menuChoice == AttriMenu::Return)
		{
			return;
		}

		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();

		switch (menuChoice)
		{
			case AttriMenu::Attributes:
				{
					myPlayer.PrintDerivedAttributes();
					break;
				}
			case AttriMenu::DerivedAttributes:
				{
					myPlayer.PrintAttributes();
					break;
				}
			case AttriMenu::Return:
				{
					return;
				}
		}
		system("pause");
		return;
	}
}

void PlayerController::Win() const
{
	std::cout << "\nYou reached the last room (" << myPlayer.GetName() << ")!\n";
	std::cout << "Closing game...\n";
	system("pause");
	myPlayer.SetIsDead(true);
	return;
}

//PRINTS
void PlayerController::PrintNavigation() const
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

void PlayerController::PrintPickupMenu() const
{
	std::cout
		<< "\n<--- Pickup --->\n";
	auto& items = currentRoom->GetLootInRoom();
	if (items.empty())
	{
		return;
	}

	for (int i = 0; i < static_cast<int>(items.size()); ++i)
	{
		std::cout << (i + 1) << ") ";
		items[i].PrintItemOnDisplay();
		std::cout << "\n";
	}

	std::cout << static_cast<int>(items.size()) + 1 << ") Return\n"
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
			<< "|" << currentRoom->GetChestInRoom()[i].GetName() << "|" << "\n";
	}

	std::cout << static_cast<int>(currentRoom->GetChestInRoom().size()) + 1 << ") Return\n"
		<< "Choice: ";
}

void PlayerController::PrintSpells() const
{
	std::cout << "\n<--- Read spell --->\n";

	auto spells = currentRoom->GetSpellsInRoom();
	if (spells.empty())
	{
		return;
	}

	const int SPELLS_AMOUNT = static_cast<int>(spells.size());

	for (int i = 0; i < SPELLS_AMOUNT; ++i)
	{
		std::cout << (i + 1) << ") ";
		spells[i].PrintSpellOnDisplay();
		std::cout << "\n";
	}
	std::cout << SPELLS_AMOUNT + 1 << ") Return\n"
		<< "Choice: ";
}
