#include "PlayerController.h"
#include "WorldMap.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "Cheats.h"
#include "Item.h"

#include <vector>
#include <iostream>
#include <cmath>

using namespace Utils;

PlayerController::PlayerController(WorldMap& aWorldMap, Player& aPlayer)
	: myWorldMap(aWorldMap), myPlayer(aPlayer), currentRoom(nullptr)
{
}

void PlayerController::UpdateAction()
{
	while (true && !myPlayer.IsDead())
	{
		currentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
		myPlayer.SetRoomId(currentRoom->GetRoomId());
		PrintUI();

		if (currentRoom->GetEnemies().empty())
		{
			PrintActionMenu(false, true);
		}
		else
		{
			PrintActionMenu(true, true);
		}

		Action actionChoice = static_cast<Action>(ReadIntInRange(
			static_cast<int>(Action::Combat),
			static_cast<int>(Action::Quit)));

		switch (actionChoice)
		{
			case Action::Combat:
				{
					while (com)
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
					Cheats::UpdateCheats();
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

void PlayerController::UpdateCombat() const
{
}

void PlayerController::UpdateNavigation()
{
	while (true && !myPlayer.IsDead())
	{
		PrintUI();
		myWorldMap.PrintMap(myPlayer.GetPosition());
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
		std::cout << "You healed to full hp: " << std::round(myPlayer.GetAttributes().currentHealth)
			<< " -> " << std::round(myPlayer.GetAttributes().maxHealth) << "\n";
		myPlayer.HealFullHealth();

		if (myPlayer.GetRoomId() == 5)
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
		PrintUI();

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
		PrintUI();
		auto& items = currentRoom->GetLootInRoom();

		PrintPickupMenu();
		if (items.empty())
		{
			std::cout << "(No loot here...)\n";
			system("pause");
			return;
		}
		constexpr int offset = 1;
		const int itemCount = static_cast<int>(items.size());
		const int returnIndex = itemCount + offset;

		int menuChoice = ReadIntInRange(offset, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		const int itemIndex = menuChoice - 1;

		const auto& itemToPickup = items[itemIndex];

		if (!myPlayer.CanPickupItem(itemToPickup))
		{
			std::cout << "\n(Item too heavy to pickup)\n";
		}
		else
		{
			myPlayer.PickupItem(itemToPickup);

			if (myPlayer.GetEquipment().CanEquipItem(itemToPickup))
			{
				myPlayer.EquipItem(itemToPickup.GetId());
			}

			items.erase(items.begin() + itemIndex);
		}
		system("pause");
	}
}

//chests sometimes dissapear and sometimes not, items dissapear if slots are taken and trying to equip
//its 01:46 rn and I discovered what guard clausing is and it changed my life foerver.
void PlayerController::UpdateLootChests() const
{
	while (true && !myPlayer.IsDead())
	{
		PrintUI();

		PrintChestMenu();

		auto& chests = currentRoom->GetChestInRoom();

		if (chests.empty())
		{
			std::cout << "(No chests here...)\n";
			system("pause");
			return;
		}

		const int chestCount = static_cast<int>(chests.size());
		const int returnIndex = chestCount + 1;

		int menuChoice = ReadIntInRange(1, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		const int chestIndex = menuChoice - 1;
		Chest& chest = chests[chestIndex];
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
			chests.erase(currentRoom->GetChestInRoom().begin() + chestIndex);
			system("pause");
			return;
		}

		for (const auto& item : loot)
		{
			currentRoom->AddItemToRoom(item);
		}
		std::cout << "\n|" << chest.GetName() << "|"
			<< " has been opened and dropped items on the floor!\n";

		chests.erase(currentRoom->GetChestInRoom().begin() + chestIndex);
		system("pause");
		return;
	}
}

void PlayerController::UpdateReadSpells() const
{
	while (true && !myPlayer.IsDead())
	{
		PrintUI();
		auto& spells = currentRoom->GetSpellsInRoom();
		PrintSpells();

		if (spells.empty())
		{
			std::cout << "(No spells here...)\n";
			system("pause");
			return;
		}

		const int spellsCount = static_cast<int>(spells.size());
		const int returnIndex = spellsCount + 1;
		int menuChoice = ReadIntInRange(1, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		const int spellIndex = menuChoice - 1;
		const Spell& spell = spells[spellIndex];

		myPlayer.AddSpell(spell);

		spells.erase(spells.begin() + spellIndex);
		system("pause");
	}
}

void PlayerController::UpdateInventory() const
{
	while (true && !myPlayer.IsDead())
	{
		PrintUI();
		PrintInventoryMenu();

		constexpr int equipmentIndex = 1;
		constexpr int returnIndex = 4;

		int menuChoice = ReadIntInRange(equipmentIndex, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		switch (menuChoice)
		{
			case 1:
				{
					UpdateEquipment();
					break;
				}
			case 2:
				{
					UpdateInventoryItems();
					break;
				}
			case 3:
				{
					UpdateSpellBook();
					break;
				}
		}
	}
}

void PlayerController::UpdateEquipment() const
{
	while (true && !myPlayer.IsDead())
	{
		PrintUI();

		const auto& equipment = myPlayer.GetEquipment();
		equipment.PrintEquipment();

		constexpr int offsetIndex = 1;
		const int returnIndex = static_cast<int>(equipment.GetEquipment().size()) + offsetIndex;

		std::cout << returnIndex << ") Return\n";

		int menuChoice = ReadIntInRange(offsetIndex, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}
		const int itemSlotIndex = menuChoice - offsetIndex;
		auto& item = equipment.GetEquipment()[itemSlotIndex];
		std::cout << "\n";
		item->PrintItemOnDisplay();

		std::cout << "\nUnequip item?\n"
			<< "1) Yes\n"
			<< "2) No\n"
			<< "Choice: ";

		int unequipChoice = ReadIntInRange(1, 2);

		if (unequipChoice == 2)
		{
			return;
		}

		myPlayer.UnequipItem(itemSlotIndex);
		system("pause");
	}
}

void PlayerController::UpdateInventoryItems() const
{
	while (true && !myPlayer.IsDead())
	{
		PrintUI();
		const auto& inventory = myPlayer.GetInventory();
		inventory.PrintInventory(myPlayer.GetAttributes().carryCapacity);

		const int offsetIndex = 1;
		const int returnIndex = static_cast<int>(inventory.GetItems().size()) + offsetIndex;

		int menuChoice = ReadIntInRange(offsetIndex, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		const int itemIndex = menuChoice - offsetIndex;
		const auto& item = inventory.GetItems()[itemIndex];

		if (itemIndex < 0 || itemIndex >= static_cast<int>(inventory.GetItems().size()))
		{
			continue;
		}

		std::cout << "\n";
		item.PrintItemOnDisplay();

		std::cout << "\nItem Action\n"
			<< "1) Equip\n"
			<< "2) Drop\n"
			<< "3) Return\n"
			<< "Choice: ";

		menuChoice = ReadIntInRange(static_cast<int>(ItemAction::Equip), static_cast<int>(ItemAction::Count));
		ItemAction itemAction = static_cast<ItemAction>(menuChoice);

		switch (itemAction)
		{
			case ItemAction::Equip:
				{
					if (myPlayer.GetEquipment().CanEquipItem(item))
					{
						myPlayer.EquipItem(item.GetId());
					}
					else
					{
						std::cout << "\nCan't equip item if item slot is occupied!\n";
					}
					break;
				}
			case ItemAction::Drop:
				{
					currentRoom->AddItemToRoom(item);
					myPlayer.DropItem(item.GetId());
					break;
				}
			default:
				{
					return;
				}
		}
		system("pause");
	}
}

void PlayerController::UpdateSpellBook() const
{
	while (true && !myPlayer.IsDead())
	{
		system("cls");
		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemies();

		const auto& spellbook = myPlayer.GetSpellBook();
		spellbook.PrintSpells();

		const int offsetIndex = 1;
		int spellsUnactiveCount = static_cast<int>(spellbook.GetInactiveSpells().size());

		const int returnIndex = spellsUnactiveCount + offsetIndex;
		int menuChoice = ReadIntInRange(offsetIndex, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		const int spellIndex = menuChoice - offsetIndex;
		if (spellIndex < 0 || spellIndex >= spellsUnactiveCount)
		{
			continue;
		}
		const Spell* spell = spellbook.GetInactiveSpells()[spellIndex];
		const int spellId = spell->GetId();

		std::cout << "\nRead spell?\n"
			<< "1) Yes\n"
			<< "2) No\n"
			<< "Choice: ";

		int spellChoiceInt = ReadIntInRange(static_cast<int>(Choice::Yes), static_cast<int>(Choice::No));
		Choice spellChoice = static_cast<Choice>(spellChoiceInt);

		if (spellChoice == Choice::No)
		{
			return;
		}
		myPlayer.ActivateSpell(spellId);
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

void PlayerController::PrintUI() const
{
	system("cls");
	myPlayer.PrintPlayerUI();
	currentRoom->PrintEnemies();
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
	std::cout << "\n<--- Pickup spell --->\n";

	const auto& spells = currentRoom->GetSpellsInRoom();
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

void PlayerController::PrintInventoryMenu() const
{
	std::cout
		<< "\n<--- Inventory --->\n"
		<< "1) Equipment\n"
		<< "2) Items\n"
		<< "3) Spells\n"
		<< "4) Return\n"
		<< "Choice: ";
}
