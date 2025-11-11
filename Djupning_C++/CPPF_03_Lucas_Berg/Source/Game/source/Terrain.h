#pragma once
#include "SharedTypes.h"
#include "GameState.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
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
	void ResumeTerrainMovement();
	void UpdateTerrainData();

	std::vector<TerrainPiece>& GetPieces() { return myPieces; }

private:
	Tga::Engine* myEngine;
	GameState* myGameState;
	Tga::Vector2f myScreenResolution;

	std::vector<TerrainPiece> myPieces;

	TerrainData myTerrainData = {6.0f, 50.0f};

	float myUpdateTerrainTimer = 0;
	float myUpdateTerrainDuration = 3;

	int myNextId;
	float myTimer;
	float myFloorSpawn;
	float myCeilingSpawn;
	float myOffset = -200;
	float myGap = 0;

	struct Obstacle
	{
		float timer;
		float timeToSpawn;
		float height;

		const float obsTimeToSpawnMin = 0.75f;
		const float obsTimeToSpawnMax = 3.0f;
	};

	Obstacle myObstacle = {0.0f, 3.0f, 700.0f};
};
