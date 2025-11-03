#pragma once
#include "Config.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"
#include "CommonUtilities/Timer.h"

using Timer = CommonUtilities::Timer;

class Helicopter
{
public:
	Helicopter();
	~Helicopter();

	void Init(Tga::Engine& aEngine);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer) const;

	void SetVisibility(bool aVisible) { myIsVisible = aVisible; }
	bool IsVisible() const { return myIsVisible; }

	void SetDirection(Direction aDirection);
	void SetPosition(Tga::Vector2f aPosition);
	Tga::Vector2f GetPosition() const { return myPosition; }
	Tga::Vector2f GetSize() const { return mySprite.instance.mySize; }

	float CalculateVelocity(float aTimeDelta);
	float CheckBounds(float aTimeDelta);

	MovementData GetMovementData() const { return myMovement; }
	JumpData GetJumpData() const { return myJumpData; }
	bool CheckCollision(Tga::Vector2f aPosition, Tga::Vector2f aSize) const;

private:
	SpriteData mySprite = {{}, {}, "Sprites/FireBall.png"};
	bool myIsVisible = true;

	Tga::Vector2f myPosition;
	Tga::Vector2f myScreenResolution;

	Bounds myBounds;

	MovementData myMovement;
	JumpData myJumpData = {false, 50.0f, 1.0f};
};
