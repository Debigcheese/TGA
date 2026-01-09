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

	void Welcome();
	void EnterUsername(Player& aPlayer);
	void Intro(const Player& aPlayer);

private:
	WorldMap worldMap;
};

