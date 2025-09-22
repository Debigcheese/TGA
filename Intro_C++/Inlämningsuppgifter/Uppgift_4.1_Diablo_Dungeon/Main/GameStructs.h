#pragma once
#include <vector>
#include "GameEnums.h"
class Room; // fwd declare (pointer only)

struct PlayerAttributes
{
	float strength = 10; //styrka (10-99)
	float agility = 10; // smidighet (10-99)
	float endurance = 10; // fysik (10-99)
	float myCurrentHealth = 0;
};

struct EnemyAttributes
{
	EnemyType myType;
	const char* myName;
	float myDamage;
	float myMaxHealth;
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

