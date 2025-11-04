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

	void SetId(int aId);
	void SetSpawn(float aHeight, Direction aDirection);
	void SetSpeed(Tga::Vector2f aMovementSpeed) { myMovement.speed = aMovementSpeed; }

	int GetId() const { return myId; }
	Tga::Vector2f GetPosition() const { return myPosition; }
	Tga::Vector2f GetSize() const { return mySprite.instance.mySize; }

	bool GetIsActive() const { return myIsActive; }
	Direction GetDirection() const { return myDirection; }
	bool GetHasScored() const { return myHasScored; }
	void SetHasScored() { myHasScored = true; }

private:
	SpriteData mySprite = {{}, {}, "Sprites/StoneTerrain.png"};

	Tga::Vector2f myPosition;
	Tga::Vector2f myScreenResolution;

	MovementData myMovement;
	Direction myDirection;

	bool myHasScored = false;
	bool myIsActive = false;
	int myId;
};
