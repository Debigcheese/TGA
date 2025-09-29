#pragma once
#include "WorldMap.h"
#include "Player.h"
#include "Room.h"

// EVERY WHILE LOOP + READ INPUT (MENU CHOICES) IS HANDLED IN THIS CLASS
class PlayerController
{
public:
	PlayerController(WorldMap& aWorldMap, Player& aPlayer);

	void UpdateAction();
	void UpdateCombat();
	void UpdateNavigation();

	void UpdateScavenge();
	void UpdatePickupItem() const;
	void UpdateLootChests() const;
	void UpdateReadSpells() const;
	void UpdateInventory() const;
	void UpdateAttributes() const;
	void Win() const;

	void PrintNavigation() const;
	void PrintActionMenu(bool aEnemiesExist, bool aShowCheats) const;
	void PrintScavenge() const;
	void PrintPickupMenu() const;
	void PrintChestMenu() const;

	void PrintSpells() const;

private:
	Room* currentRoom;
	WorldMap& myWorldMap;
	Player& myPlayer;
};
