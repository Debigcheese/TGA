#pragma once
#include <tge/sprite/sprite.h>

enum class Actor
{
	None,
	Player,
	Enemy,
};

struct SpriteData
{
	Tga::Sprite2DInstanceData instance{};
	Tga::SpriteSharedData sharedData{};
};

struct Score
{
	int playerScore;
	int enemyScore;
};

struct Bounds
{
	float maxY;
	float minY;
	float maxX;
	float minX;
};

enum class Direction
{
	None = 0,
	Up = 1,
	Down = 0
};

struct MovementData
{
	float flyPower;
	float accelerationTime;

	Direction direction;

	Tga::Vector2f speed;
	Tga::Vector2f acceleration;
	Tga::Vector2f maxSpeed;
	Tga::Vector2f velocity;
};

struct Clamp
{
	float maxY;
	float minY;
};

struct TerrainSpawn
{
	float myTimer;

	float myFloorSpawn;
	float myCeilingSpawn;
	float offset = -100;

	int nextId;
};

struct TerrainData
{
	float frequency;
	float amplitude;
};
