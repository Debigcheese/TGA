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

struct LerpData
{
	float current = 1.0f;
	float defaultValue = 1.0f;
	float target = 1.0f;
	float timer = 0.0f;
	float duration = 1.0f;
	float lerpValue = 1.0f;
	bool isLerping = false;
};

struct JumpData
{
	bool isJumping;
	float jumpHeight;
	float jumpDuration;
	float timer = 0.0f;
};

struct MovementData
{
	Tga::Vector2f speed;
	Tga::Vector2f acceleration;
	Tga::Vector2f maxSpeed;
	Tga::Vector2f velocity;

	Direction direction;
	//bool is
	float accelerationTime;
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
