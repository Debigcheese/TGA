#pragma once
#include "GameEnums.h"
#include "GameConstants.h"

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
	int X;
	int Y;

	Position operator+(const Position& other) const
	{
		return {X + other.X, Y + other.Y};
	}

	bool operator==(const Position& other) const
	{
		return (X == other.X && Y == other.Y);
	}
};
