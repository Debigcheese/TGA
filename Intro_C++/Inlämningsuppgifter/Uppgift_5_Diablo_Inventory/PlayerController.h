#pragma once
#include "WorldMap.h"
#include "Player.h"
#include "Room.h"
#include "CombatManager.h"

// EVERY WHILE LOOP + READ INPUT (MENU CHOICES) IS HANDLED IN THIS CLASS
class PlayerController
{
public:
	PlayerController(WorldMap& aWorldMap, Player& aPlayer);

	void UpdateAction();
	void UpdateNavigation();

	void UpdateScavenge();
	void UpdatePickupItem() const;
	void UpdateLootChests() const;
	void UpdateReadSpells() const;

	void UpdateInventory() const;
	void UpdateEquipment() const;
	void UpdateInventoryItems() const;
	void UpdateSpellBook() const;

	void UpdateAttributes() const;
	void Win() const;

	void PrintUI() const;
	void PrintNavigation() const;
	void PrintActionMenu(bool aEnemiesExist, bool aShowCheats) const;
	void PrintScavenge() const;
	void PrintPickupMenu() const;
	void PrintChestMenu() const;
	void PrintSpells() const;
	void PrintInventoryMenu() const;

private:
	Room* myCurrentRoom;
	WorldMap& myWorldMap;
	Player& myPlayer;
	CombatManager myCombatManager;
};
