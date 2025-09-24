#pragma once
#include <vector>
#include "GameEnums.h"
#include "GameConstants.h"

class Room; // fwd declare
using namespace GameConstants;

struct PlayerAttributes
{
	float strength = STRENGTH_BASE; //styrka (10-99)
	float agility = AGILITY_BASE; // smidighet (10-99)
	float endurance = ENDURANCE_BASE; // fysik (10-99)
	float myCurrentHealth = HEALTH_ZERO;
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
	LockRequirements strengthReq{LockType::LockType_Strength, LOCK_1_STRENGTH_REQ_DECLARE};
	LockRequirements agilityReq{LockType::LockType_Agility, LOCK_1_AGILITY_REQ_DECLARE};
};

struct Position
{
	int pos_X;
	int pos_Y;
};
