#pragma once
#include "WorldMap.h"
#include "Player.h"

class Diablo
{
public:
	Diablo();
	void RunDiablo();

private:
	WorldMap myWorldMap;
	Player myPlayer;
};

