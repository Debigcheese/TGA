#pragma once

enum class Direction
{
	None = 0,
	West = 1,
	North = 2,
	East = 3,
	South = 4,
};

enum class Action
{
	None = 0,
	Combat = 1,
	Navigation = 2,
	LookAround = 3,
	Attributes = 4,
	Cheats = 5,
	Quit = 6,
};

enum class AttackType
{
	None = 0,
	QuickAttack = 1,
	HeavyAttack = 2,
};

enum class AttriMenu
{
	Attributes = 1,
	DerivedAttributes = 2,
	Return = 3,
};

enum class LookAround
{
	Scavenge = 1,
	OpenChest = 2,
	Return = 3,
};

enum class LockType
{
	None = 0,
	Agility = 1,
	Strength = 2,
	Unlocked = 3,
};

enum class EnemyType
{
	None = 0,
	Bat = 1,
	Skeleton = 2,
	Undead = 3,
	Beast = 4,
	Humanoid = 5,
	Elemental = 6,
	Demon = 7,
};

enum class CheatType
{
	None = 4,
	Invincible = 1,
	OneShot = 2,
	Ghost = 3,
};

enum class AttributeType
{
	None = 0,
	Strength = 1, //styrka (10-99)
	Agility = 2, // smidighet (10-99)
	Endurance = 3, // fysik (10-99)
	MaxHealth = 4,
	CurrentHealth = 5,
	CarryCapacity = 6,
	Damage = 7,
	Defense = 8,
};

enum class ItemType
{
	None = 0,
	Armor = 1,
	Weapon = 2,
	Spell = 3,
};

enum class Rarity
{
	None = 0,
	Bronze = 1,
	Silver = 2,
	Gold = 3,
	Legendary = 4,
};

enum class TextColor
{
	Red,
	Brown,
	Silver,
	Gold,
	Magenta
};
