#pragma once
#include "WorldMap.h"
#include "Player.h"
#include "Room.h"

class PlayerController
{
public:
	PlayerController(WorldMap& aWorldMap, Player& aPlayer);

	void UpdateAction();
	void UpdateCombat();
	void UpdateNavigation();
	void UpdateLookAround();
	void UpdatePickupItem(std::vector<Item>& aItems) const;
	void UpdateInventory();


	void Win() const;

	void PrintNavigation() const;
	void PrintActionMenu(bool aEnemiesExist, bool aShowCheats) const;
	void PrintLookAround() const;
	void PrintPickupMenu(const std::vector<Item>& aLoot) const;

private:
	Room* currentRoom;
	WorldMap& myWorldMap;
	Player& myPlayer;
};
