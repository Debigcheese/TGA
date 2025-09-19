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

	void PrintNavigation();
	void PrintLocation(const int aRoomId);

private:
	Nav myNav;
	WorldMap myWorldMap;
	Player myPlayer;
};

