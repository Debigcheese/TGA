#pragma once
#include "GameStructs.h"

class Player;
class Room;
class WorldMap;
class Door;

class NavigationController
{
public:
	NavigationController(WorldMap& aWorldMap, Player& aPlayer);

	void UpdateDoorLock(Door& aDoor) const;
	void UpdateNavigation();
	Room* GetLookForRoom(const Position& aLookForPos) const;
	bool HandleEnemyAggro() const;

private:
	Player& myPlayer;
	WorldMap& myWorldMap;
	Room* myCurrentRoom;
};
