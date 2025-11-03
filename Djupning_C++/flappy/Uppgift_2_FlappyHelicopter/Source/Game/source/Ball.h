#pragma once
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"

class Ball
{
public:
	Ball();
	~Ball();

	void Init(Tga::Engine& aEngine);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);
	void Disable();
	void Reset();

	Tga::Vector2f GetPosition() const { return myPosition; }
	Tga::Vector2f GetSize() const { return mySpriteInstance.mySize; }
	void SetRandomPos();
	void SetRandomDirection();

	void SwitchDirection();
	bool CheckCollision(Tga::Vector2f aPosition, Tga::Vector2f aSize) const;
	void ResolveCollision(const Tga::Vector2f& aPosition, const Tga::Vector2f& aColliderSize);

	void SetDirection(Tga::Vector2f aDirection) { myDirection = aDirection; }
	Tga::Vector2f GetDirection() const { return myDirection; }

	void SetVisibility(bool aVisible) { myIsVisible = aVisible; }
	bool IsVisible() const { return myIsVisible; }

	void Bounce();

private:
	Tga::Sprite2DInstanceData mySpriteInstance = {};
	Tga::SpriteSharedData mySharedData = {};

	float myTimeToSpawn = 0.0f;
	int myBounceCounter;
	bool myIsVisible = true;

	Tga::Vector2f myStartingSpeed;

	Tga::Vector2f myStartingPosition;
	Tga::Vector2f myPosition;
	Tga::Vector2f myDirection;
	Tga::Vector2f myVelocity;
	Tga::Rotator myRotation;
	Tga::Vector2f mySpeed;
	Tga::Vector2f myScreenResolution;
};
