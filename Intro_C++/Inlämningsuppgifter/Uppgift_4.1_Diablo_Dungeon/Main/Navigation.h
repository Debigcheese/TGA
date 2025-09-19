#pragma once
#include "WorldMap.h"
#include "Player.h"
#include "GameEnums.h"
#include "GameStructs.h"

class Navigation
{
public:
	Navigation(WorldMap aWorldMap, Player aPlayer);
	void UpdateNavigation();

	std::vector<Direction> GetValidDirections();
	void PrintNavigation();
	void PrintLocation(const int aRoomId);
	bool DoesDoorExistInDirection();

private:
	Nav myNav;
	WorldMap myWorldMap;
	Player myPlayer;
};

