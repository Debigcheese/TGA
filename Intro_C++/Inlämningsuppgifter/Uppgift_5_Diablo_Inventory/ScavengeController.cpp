#include "ScavengeController.h"
#include "Enemy.h"
#include "Utils.h"
#include "Cheats.h"
#include "Item.h"
#include "ConsoleUI.h"

#include <vector>
#include <iostream>
#include <cmath>

using namespace ConsoleUI;

ScavengeController::ScavengeController(Player& aPlayer) : myPlayer(aPlayer), myCurrentRoom(nullptr)
{
}

void ScavengeController::UpdateScavenge(Room* aCurrentRoom)
{
	myCurrentRoom = aCurrentRoom;
	if (!myCurrentRoom->GetEnemies().empty() && !Cheats::GetCheats().ghost)
	{
		std::cout << "You try scavenging the room but get attacked!\n\n";
		for (Enemy& enemy : myCurrentRoom->GetEnemies())
		{
			enemy.Attack(myPlayer);
		}
		Pause();
		return;
	}
	while (true && !myPlayer.IsDead())
	{
		PrintUI(myPlayer, *myCurrentRoom);

		PrintScavengeMenu();

		auto menuChoice = static_cast<Scavenge>(Utils::ReadIntInRange(
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

void ScavengeController::UpdatePickupItem() const
{
	while (true && !myPlayer.IsDead())
	{
		auto& items = myCurrentRoom->GetLootInRoom();
		PrintUI(myPlayer, *myCurrentRoom);
		PrintPickupMenu(items);

		if (items.empty())
		{
			Pause();
			return;
		}

		constexpr int offset = 1;
		const int itemCount = static_cast<int>(items.size());
		const int returnIndex = itemCount + offset;

		int menuChoice = Utils::ReadIntInRange(offset, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		const int itemIndex = menuChoice - 1;
		const auto& itemToPickup = items[itemIndex];

		if (!myPlayer.CanPickupItem(itemToPickup))
		{
			std::cout << "\n(Item too heavy to pickup)\n";
			Pause();
			continue;
		}

		myPlayer.PickupItem(itemToPickup);
		if (myPlayer.GetEquipment().CanEquipItem(itemToPickup))
		{
			myPlayer.EquipItem(itemToPickup.GetId());
		}
		else
		{
			myPlayer.GetInventory().PrintItemAdded(itemToPickup);
		}
		items.erase(items.begin() + itemIndex);


		Pause();
	}
}

void ScavengeController::UpdateLootChests() const
{
	while (true && !myPlayer.IsDead())
	{
		auto& chests = myCurrentRoom->GetChestInRoom();
		PrintUI(myPlayer, *myCurrentRoom);
		PrintChestMenu(chests);

		if (chests.empty())
		{
			Pause();
			return;
		}

		const int chestCount = static_cast<int>(chests.size());
		const int returnIndex = chestCount + 1;

		int menuChoice = Utils::ReadIntInRange(1, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		const int chestIndex = menuChoice - 1;
		Chest& chest = chests[chestIndex];
		if (chest.GetIsOpen())
		{
			std::cout << "\n(Chest already open)\n";
			Pause();
			continue;
		}

		const auto loot = chest.Open(); //returns items & empties chest

		if (loot.empty())
		{
			std::cout << "\n|" << chest.GetName() << "|"
				<< " opened but was empty...\n";
			chests.erase(myCurrentRoom->GetChestInRoom().begin() + chestIndex);
			Pause();
			return;
		}

		std::cout << "\n|" << chest.GetName() << "|"
			<< " has been opened and dropped items on the floor!\n";

		for (const auto& item : loot)
		{
			myCurrentRoom->AddItemToRoom(item);
		}

		chests.erase(myCurrentRoom->GetChestInRoom().begin() + chestIndex);
		Pause();
		return;
	}
}

void ScavengeController::UpdateReadSpells() const
{
	while (true && !myPlayer.IsDead())
	{
		auto& spells = myCurrentRoom->GetSpellsInRoom();
		PrintUI(myPlayer, *myCurrentRoom);
		PrintSpellBookMenu(spells);

		if (spells.empty())
		{
			Pause();
			return;
		}

		const int spellsCount = static_cast<int>(spells.size());
		const int returnIndex = spellsCount + 1;
		int menuChoice = Utils::ReadIntInRange(1, returnIndex);

		if (menuChoice == returnIndex)
		{
			return;
		}

		const int spellIndex = menuChoice - 1;
		const Spell& spell = spells[spellIndex];

		myPlayer.AddSpell(spell);

		spells.erase(spells.begin() + spellIndex);
		Pause();
	}
}
