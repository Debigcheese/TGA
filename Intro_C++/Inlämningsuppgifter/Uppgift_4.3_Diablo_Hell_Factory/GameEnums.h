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
	Inventory = 4,
	Attributes = 5,
	Cheats = 6,
	Quit = 7,
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

enum class Scavenge
{
	Floor = 1,
	Chests = 2,
	Spells = 3,
	Return = 4,
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

enum class ItemTypes
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

enum class ItemKey
{
	None = 0,
	Eclipse = 1,
	GodSword = 2,
	Aegis = 3,
	Backpack = 4,
	StormBreaker = 5,
	DragonScale = 6,
	RustyDagger = 7,
	KnightHelm = 8,
	BloodFang = 9,
	CelestialShield = 10,
	WarAxe = 11,
	LeatherBoots = 12,
	VoidReaver = 13,
	IronChestplate = 14,
	TrainingSword = 15,
	Count
};

enum class SpellKey
{
	None = 0,
	MagicMissile = 1,
	Fireball = 2,
	MeteorStrike = 3,
	ChainLightning = 4,
	FrostBolt = 5,
	Blizzard = 6,
	PoisonDart = 7,
	AcidSpray = 8,
	TimeWarp = 9,
	Earthquake = 10,
	StoneSkin = 11,
	Shockwave = 12,
	PhoenixFlame = 13,
	WindSlash = 14,
	Hurricane = 15,
	HealingLight = 16,
	DivineShield = 17,
	ArcaneBlast = 18,
	BlackHole = 19,
	NecroticGrasp = 20,
	Count
};


enum class EnemyKey
{
	None = 0,
	Bat = 1,
	Skeleton = 2,
	Undead = 3,
	Beast = 4,
	Humanoid = 5,
	Elemental = 6,
	Demon = 7,
	Count
};
