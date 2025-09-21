#pragma once

enum class Direction
{
	None = 0,
	West = 1,
	North = 2,
	East = 3,
	South = 4,
};

enum class LockCheck
{
	Unlocked = 0,
	Agility = 1,
	Strength = 2,
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