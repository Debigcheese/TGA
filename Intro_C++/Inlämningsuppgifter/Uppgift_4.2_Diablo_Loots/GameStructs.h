#pragma once
#include <vector>
#include "GameEnums.h"

class Room; // fwd declare

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
	Direction currentDirection = Direction::Direction_None;
	std::vector<Direction> doorDirections;
};

struct LockRequirements
{
	LockType lockType = LockType::LockType_Unlocked;
	float attributeValue;
};

struct Lock
{
	bool isLocked;
	LockRequirements strengthReq{ LockType::LockType_Strength, 0 };
	LockRequirements agilityReq{ LockType::LockType_Agility, 0 };
};

struct Position
{
	int pos_X;
	int pos_Y;
};

