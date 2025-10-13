#pragma once
#include "GameStructs.h"

class Player;
class Room;
class WorldMap;

class NavigationController
{
public:
	NavigationController(WorldMap& aWorldMap, Player& aPlayer);

	void UpdateNavigation(Room* aRoom);
	Room* GetLookForRoom(const Position& aLookForPos) const;
	bool HandleEnemyAggro() const;

private:
	Player& myPlayer;
	WorldMap& myWorldMap;
	Room* myCurrentRoom;
};
