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
	void UpdatePickupItem(std::vector<Item>& aItems) const;
	void UpdateLootChests() const;
	void UpdateInventory();

	void Win() const;

	void PrintNavigation() const;
	void PrintActionMenu(bool aEnemiesExist, bool aShowCheats) const;
	void PrintScavenge() const;
	void PrintPickupMenu(const std::vector<Item>& aLoot) const;
	void PrintChestMenu() const;

private:
	Room* currentRoom;
	WorldMap& myWorldMap;
	Player& myPlayer;
};
