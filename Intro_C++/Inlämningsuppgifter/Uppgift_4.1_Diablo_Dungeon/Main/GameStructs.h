#pragma once
#include "GameEnums.h"
#include "Room.h"
#include "Door.h"

struct PlayerAttributes
{
	float strength = 10; //styrka
	float agility = 10; // smidighet
	float endurance = 10; // fysik
	float myCurrentHealth = 0;
};

// navigation
struct Nav
{
	Room currentRoom;
	Direction currentDirection = Direction::None;
	std::vector<Direction> doorDirections;
	std::vector<Door>doorsInRoom;
};