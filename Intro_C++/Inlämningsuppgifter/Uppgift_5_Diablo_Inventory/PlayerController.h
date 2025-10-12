#pragma once
#include "CombatController.h"
#include "LoadoutController.h"
#include "NavigationController.h"
#include "ScavengeController.h"

class Player;
class WorldMap;

// MASTER CONTROLLER FOR MENU CHOICES
class PlayerController
{
public:
	PlayerController(WorldMap& aWorldMap, Player& aPlayer);

	void UpdateAction();
	void UpdateAttributes() const;

	bool IsInFinalRoom() const;
	void Win() const;

private:
	Room* myCurrentRoom;
	WorldMap& myWorldMap;
	Player& myPlayer;
	CombatController myCombatController;
	ScavengeController myScavengeController;
	LoadoutController myLoadoutController;
	NavigationController myNavController;
};
