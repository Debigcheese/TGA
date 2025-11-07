#pragma once
#include "Ball.h"
#include "Config.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"

class Paddle
{
public:
	Paddle();
	~Paddle();

	void Init(Tga::Engine& aEngine, Actor aActor);
	void Update(float aTimeDelta);

	void SetDirection(Tga::Vector2f aDirection);
	void Render(Tga::SpriteDrawer& aSpriteDrawer) const;
	void SetPosition(Tga::Vector2f aPosition);

	void SetVisibility(bool aVisible) { myIsVisible = aVisible; }
	bool IsVisible() const { return myIsVisible; }

	Tga::Vector2f GetPosition() const;
	Tga::Vector2f GetSize() const;
	Tga::Vector2f GetDirection() const { return myDirection; }

	Tga::TextureResource* GetTexture(Tga::Engine& aEngine, Actor aActor) const;

private:
	Tga::Sprite2DInstanceData mySpriteInstance = {};
	Tga::SpriteSharedData mySharedData = {};

	Ball* myBall;
	Bounds myBounds;
	bool myIsVisible = true;

	Tga::Vector2f myPivot;
	Tga::Vector2f myPosition;
	Tga::Vector2f mySpeed;
	Tga::Vector2f myDirection;
	Tga::Vector2f myScreenResolution;
};
