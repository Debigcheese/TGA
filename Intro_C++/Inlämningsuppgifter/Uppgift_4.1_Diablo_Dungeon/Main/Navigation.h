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

private:
	Nav myNav;
	WorldMap myWorldMap;
	Player myPlayer;
};

