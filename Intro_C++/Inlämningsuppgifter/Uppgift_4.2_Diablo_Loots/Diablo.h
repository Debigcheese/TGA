#pragma once
#include "WorldMap.h"
#include "PlayerController.h"
#include "Player.h"

class Diablo
{
public:
	Diablo();
	void RunDiablo();

	void Welcome();
	void EnterUsername(Player& aPlayer);
	void Intro(const Player& aPlayer);

private:
	WorldMap myWorldMap;
	PlayerController myPlayerController;
	Player myPlayer;
};
