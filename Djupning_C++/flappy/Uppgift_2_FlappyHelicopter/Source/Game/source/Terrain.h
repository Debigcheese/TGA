#pragma once
#include "Config.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"

class Terrain
{
public:
	Terrain();
	~Terrain();

	void Init(Tga::Engine& aEngine);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer) const;

	void SetPosition(float aHeight, int aDirection);

private:
	SpriteData mySprite = {{}, {}, "Sprites/Paddle.png"};

	Tga::Vector2f myPosition;
	Tga::Vector2f myScreenResolution;

	Bounds myBounds;

	MovementData myMovement;
};
