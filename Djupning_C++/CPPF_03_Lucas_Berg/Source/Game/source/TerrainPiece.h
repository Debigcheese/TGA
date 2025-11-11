#pragma once
#include "Config.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"

class TerrainPiece
{
public:
	TerrainPiece(Tga::Engine& aEngine, int aId);
	TerrainPiece(Tga::Engine& aEngine, int aId, float aSpawnHeigth, Direction aDirection);
	~TerrainPiece();

	void Update(float aTimeDelta);
	void UpdateAnimation(float aDeltaTime);
	void Render(Tga::SpriteDrawer& aSpriteDrawer) const;

	void SetSpeed(Tga::Vector2f aMovementSpeed) { myMovement.speed = aMovementSpeed; }
	void ResetSpeed();

	int GetId() const { return myId; }
	Tga::Vector2f GetPosition() const { return myPosition; }
	Tga::Vector2f GetSize() const { return mySpriteInstance.mySize; }

	bool GetIsActive() const { return myIsActive; }
	Direction GetDirection() const { return myMovement.direction; }
	bool GetHasScored() const { return myHasScored; }
	void SetHasScored() { myHasScored = true; }

private:
	Tga::Sprite2DInstanceData mySpriteInstance{};
	Tga::SpriteSharedData mySharedData{};

	const char* myTerrainTexturePath = "Sprites/StoneTerrain.png";
	Tga::TextureResource* myObstacleTextures[5];

	Tga::Vector2f myPosition;
	Tga::Vector2f myScreenResolution;

	MovementData myMovement;

	float myCameraSpeed = 400.0f;

	float myObstacleAnimTimer = 0;
	bool myHasScored = false;
	bool myIsActive = false;
	int myId;
};
