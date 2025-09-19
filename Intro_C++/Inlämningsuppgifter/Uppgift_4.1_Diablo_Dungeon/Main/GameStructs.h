#pragma once
#include <vector>
#include "GameEnums.h"
class Room; // fwd declare (pointer only)

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
	Room* currentRoom = nullptr;
	Room* previousRoom = nullptr;
	Direction currentDirection = Direction::None;
	std::vector<Direction> doorDirections;
};

struct DoorLock
{
	LockCheck lockCheck = LockCheck::Unlocked;
	float attributeValue;
};

struct Position
{
	int pos_X;
	int pos_Y;
};