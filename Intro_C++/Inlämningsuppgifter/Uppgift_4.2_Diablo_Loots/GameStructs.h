#pragma once
#include "GameEnums.h"
#include "GameConstants.h"

using namespace GameConstants;


struct EnemyAttributes
{
	EnemyType myType;
	const char* myName;
	float myDamage;
	float myMaxHealth;
};

struct LockRequirements
{
	LockType lockType = LockType::Unlocked;
	float attributeValue;
};

struct Lock
{
	bool isLocked;
	LockRequirements strengthReq{LockType::Strength, LOCK_1_STRENGTH_REQ_DECLARE};
	LockRequirements agilityReq{LockType::Agility, LOCK_1_AGILITY_REQ_DECLARE};
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

struct Attributes
{
	float strength = 0; //styrka (10-99)
	float agility = 0; // smidighet (10-99)
	float endurance = 0; // fysik (10-99)
	float maxHealth = 0;
	float currentHealth = 0;
	float carryCapacity = 0;
	float damage = 0;
	float defense = 0;

	Attributes& operator+=(const Attributes& other)
	{
		strength += other.strength;
		agility += other.agility;
		endurance += other.endurance;
		maxHealth += other.maxHealth;
		currentHealth += other.currentHealth;
		carryCapacity += other.carryCapacity;
		damage += other.damage;
		defense += other.defense;
		return *this;
	}

	void Clear()
	{
		*this = {};
	}
};

struct SpellAttributes
{
	int id;
	Rarity rarity;
	const char* name;
	Attributes attributes;
};

struct ItemAttributes
{
	int id;
	ItemType type;
	Rarity rarity;
	const char* name;
	float weight;
	Attributes attributes;
};
