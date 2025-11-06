#pragma once
#include "Config.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"
#include "CommonUtilities/Timer.h"
#include "tge/animation/AnimationPlayer.h"

using Timer = CommonUtilities::Timer;

class Helicopter
{
public:
	Helicopter();
	~Helicopter();

	void Init(Tga::Engine& aEngine);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer) const;
	void Reset();

	void SetActive(bool aIsActive) { myIsActive = aIsActive; }
	bool IsActive() const { return myIsActive; }

	void SetDirection(Direction aDirection);
	void SetPosition(Tga::Vector2f aPosition);
	Tga::Vector2f GetPosition() const { return myPosition; }
	Tga::Vector2f GetSize() const { return mySprite.instance.mySize; }

	void UpdateAnimation(float aDeltaTime);
	float CalculateVelocity(float aTimeDelta);
	float CheckBounds(float aTimeDelta);

	MovementData GetMovementData() const { return myMovement; }
	JumpData GetJumpData() const { return myJumpData; }
	bool CheckCollision(Tga::Vector2f aPosition, Tga::Vector2f aSize) const;

private:
	SpriteData mySprite = {{}, {}};

	Tga::TextureResource* myTextures[3];

	float myAnimTimer = 0;
	bool myIsActive = true;

	Tga::Vector2f mySpawnPosition;
	Tga::Vector2f myPosition;
	Tga::Vector2f myScreenResolution;
	Tga::Vector2f myDefaultRotation;

	float myRotationTimer = 0;

	Bounds myBounds;

	MovementData myMovement;
	JumpData myJumpData = {false, 50.0f, 1.0f};
};
