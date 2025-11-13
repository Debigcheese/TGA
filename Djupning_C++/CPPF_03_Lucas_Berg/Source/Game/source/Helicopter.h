#pragma once
#include "SharedTypes.h"
#include "GameState.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"

enum class State
{
	Alive,
	Dying,
	Dead
};

class Helicopter
{
public:
	Helicopter();
	~Helicopter();

	void Init(Tga::Engine& aEngine, GameState* aGameState);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer) const;
	void Reset();

	void SetDirection(Direction aDirection);
	void SetPosition(Tga::Vector2f aPosition);
	Tga::Vector2f GetPosition() const { return myPosition; }
	Tga::Vector2f GetSize() const { return mySprite.instance.mySize; }

	void OnDeath();

	void UpdateAnimation(float aDeltaTime, Tga::TextureResource* aTextures[], size_t aFrames);
	float GetVelocity(float aTimeDelta);
	float GetRotation(float aDeltaTime);

	MovementData GetMovementData() const { return myMovement; }
	bool CheckCollision(Tga::Vector2f aPosition, Tga::Vector2f aSize) const;
	float CheckBounds(float aTimeDelta);

private:
	SpriteData mySprite = {{}, {}};
	GameState* myGameState;

	Tga::TextureResource* myTextures[3];
	Tga::TextureResource* myBloodTextures[29];

	Tga::Vector2ui myDefaultSize;
	Tga::Vector2f mySpawnPosition;
	Tga::Vector2f myPosition;
	Tga::Vector2f myScreenResolution;
	Tga::Vector2f myDefaultRotation;
	Bounds myBounds;

	State myState;
	float myDeathAnimTimer = 1;
	size_t myAnimFrame = 0;
	Tga::Vector2ui myDeathSize;

	bool myIsDead = false;
	float myAnimTimer = 0;

	float myRotationTimer = 0;
	float myGravity = 1.0f;
	MovementData myMovement;
};
