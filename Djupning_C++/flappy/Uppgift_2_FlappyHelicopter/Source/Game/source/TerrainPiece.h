#pragma once
#include "Config.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"

class TerrainPiece
{
public:
	TerrainPiece();
	~TerrainPiece();

	void Init(Tga::Engine& aEngine);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer) const;

	void SetSpawn(float aHeight, Direction aDirection);
	Tga::Vector2f GetPosition() const { return myPosition; }
	bool GetIsActive() const { return myIsActive; }
	Direction GetDirection() const { return myDirection; }

private:
	SpriteData mySprite = {{}, {}, "Sprites/StoneTerrain.png"};

	Tga::Vector2f myPosition;
	Tga::Vector2f myScreenResolution;

	MovementData myMovement;

	Direction myDirection;
	bool myIsActive = false;
};
