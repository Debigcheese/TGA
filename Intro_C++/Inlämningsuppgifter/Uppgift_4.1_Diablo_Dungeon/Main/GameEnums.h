#pragma once

enum class Direction
{
	Direction_None = 0,
	Direction_West = 1,
	Direction_North = 2,
	Direction_East = 3,
	Direction_South = 4,
};

enum class Action
{
	Action_None = 0,
	Action_Combat = 1,
	Action_Navigation = 2,
	Action_Attributes = 3,
	Action_Quit = 4,
	Action_Cheats = 5,
};

enum class AttackType
{
	AttackType_None = 0,
	AttackType_QuickAttack = 1,
	AttackType_HeavyAttack = 2,
};

enum class AttriMenu
{
	AttriMenu_Attributes = 1,
	AttriMenu_DerivedAttributes = 2,
	AttriMenu_Return = 3,
};


enum class LockType
{
	LockType_None = 0,
	LockType_Agility = 1,
	LockType_Strength = 2,
	LockType_Unlocked = 3,
};

enum class EnemyType
{
	EnemyType_None = 0,
	EnemyType_Bat = 1,
	EnemyType_Skeleton = 2,
	EnemyType_Undead = 3,
	EnemyType_Beast = 4,
	EnemyType_Humanoid = 5,
	EnemyType_Elemental = 6,
	EnemyType_Demon = 7,
};

enum class CheatType
{
	CheatType_None = 4,
	CheatType_Invincible = 1,
	CheatType_OneShot = 2,
	CheatType_Ghost = 3,
};
