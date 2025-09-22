#pragma once
#include "WorldMap.h"
#include "Navigation.h"
#include "Player.h"
#include "GameEnums.h"

class Diablo
{
public:
	Diablo();
	void RunDiablo();
	void EnterUsername(Player& aPlayer);


private:
	WorldMap worldMap;
};

