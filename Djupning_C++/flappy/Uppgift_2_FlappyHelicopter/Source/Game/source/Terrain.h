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

	void ResetTerrain();
	void StopTerrainMovement();

	std::vector<TerrainPiece*> GetPieces() const { return myPieces; }

private:
	Tga::Vector2f myScreenResolution;
	Tga::Engine* myEngine;

	std::vector<TerrainPiece*> myPieces;
	Bounds myBounds;

	float myTimer;

	float myFloorSpawn;
	float myCeilingSpawn;

	float offset = -100;

	int myNextId;
};
