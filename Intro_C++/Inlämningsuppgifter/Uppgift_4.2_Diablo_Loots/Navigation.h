#pragma once
#include "WorldMap.h"

class Navigation
{
public:
	Navigation(WorldMap& aWorldMap, Player& aPlayer);
	void UpdateNavigation();
	void UpdateAction();
	void UpdateLookAround();
	void Win() const;

	void PrintNavigation() const;
	void PrintActionMenu(bool aEnemiesExist, bool aShowCheats) const;
	void PrintLookAround() const;
private:
	Room* currentRoom;
	WorldMap& myWorldMap;
	Player& myPlayer;
};
