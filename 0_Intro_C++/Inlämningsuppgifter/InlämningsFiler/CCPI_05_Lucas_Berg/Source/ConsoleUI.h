#pragma once
#include <vector>
#include "GameStructs.h"

class Player;
class Room;
class Item;
class Chest;
class Spell;
class CombatController;

namespace ConsoleUI
{
	// General 
	void Clear();
	void Pause();

	void PrintOneLiner(std::string Line);
	void PrintUI(const Player& aPlayer, const Room* aCurrentRoom);
	void PrintActionMenu(Room* aCurrentRoom);
	void PrintPlayerWin(const Player& aPlayer);

	void PrintNavigationMenu();

	//looting
	void PrintScavengeMenu();
	void PrintPickupMenu(const std::vector<Item>& aItems);
	void PrintChestMenu(const std::vector<Chest>& aChests);
	void PrintSpellBookMenu(const std::vector<Spell>& aSpells);

	void PrintItemActionMenu();
	void PrintInventoryMenu();
	void PrintAttributesMenu();
	void PrintQuitGame();
	void PrintMap(const Position& aPlayerPos, Position aWinPosition);

	//player
	void PrintUserName(const Player& aPlayer);
	void PrintPlayerUI(const Player& aPlayer, const Room* aCurrentRoom);
	void PrintAttributes(const Player& aPlayer);
	void PrintBaseAttributes(const Player& aPlayer);
	void PrintDerivedAttributes(const Player& aPlayer);

	void PrintDoorLock(const Lock& aLock);
	void PrintLockMenu();

	void PrintCombatUI(const CombatController& aCombatController, const Player& aPlayer, const Room* aCurrentRoom);
	void PrintAttackTypeInfo(const CombatController& aCombatController, const Player& aPlayer);

	// // Player Info
	// void PrintPlayerAttributes(const Attributes& aAttributes);
	// void PrintInventory(const std::vector<Item>& aItems, float aCarryWeight, float aCarryCap);
	// void PrintEquipment(const std::vector<Item>& aEquipped);
	// void PrintActiveSpells(const std::vector<Spell>& aActiveSpells);
	//
	// // Room Info
	// void PrintRoomOverview(const Room& aRoom);
	// void PrintEnemies(const std::vector<Enemy>& aEnemies);
	// void PrintDoors(const std::vector<Door>& aDoors);
}
