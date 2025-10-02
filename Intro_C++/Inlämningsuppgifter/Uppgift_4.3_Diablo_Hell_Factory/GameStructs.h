#pragma once
#include <array>
#include <vector>

#include "GameEnums.h"
#include "GameConstants.h"

using namespace GameConstants;

struct EnemyAttributes
{
	EnemyKey key;
	const char* name;
	float damage;
	float maxHealth;
};

struct LockRequirements
{
	LockType lockType = LockType::Unlocked;
	float attributeValue;
};

struct Lock
{
	bool isLocked;
	LockRequirements strengthReq{LockType::Strength, 0};
	LockRequirements agilityReq{LockType::Agility, 0};
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
	float strength; //styrka (10-99)
	float agility; // smidighet (10-99)
	float endurance; // fysik (10-99)
	float maxHealth;
	float currentHealth;
	float carryCapacity;
	float damage;
	float defense;

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
	SpellKey key;
	Rarity rarity;
	const char* name;
	Attributes attributes;
};

struct ItemAttributes
{
	ItemKey key;
	ItemTypes type;
	Rarity rarity;
	const char* name;
	float weight;
	Attributes attributes;
};

struct AmountRange
{
	int min;
	int max;
};

//world map constants

struct EnemyRoom
{
	std::vector<EnemyKey> enemyKeys;
};

struct CreateObject
{
	int id;
	AmountRange amount;
	Rarity rarity;
};
