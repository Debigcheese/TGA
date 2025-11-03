#pragma once
#include "Config.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"
#include "TerrainPiece.h"

class Terrain
{
public:
	Terrain();
	~Terrain();

	void Init(Tga::Engine& aEngine);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer) const;

private:
	SpriteData mySprite = {{}, {}, "Sprites/Paddle.png"};

	Tga::Vector2f myPosition;
	Tga::Vector2f myScreenResolution;
	Tga::Engine* myEngine;

	std::vector<TerrainPiece*> myPieces;
	Bounds myBounds;
	float myTimer;

	MovementData myMovement;
};
