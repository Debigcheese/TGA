#include "Terrain.h"
#include "Utils.h"
#include "CommonUtilities/UtilityFunctions.h"
#include "CommonUtilities/Random.h"

Terrain::Terrain()
{
	myScreenResolution = {1920.0f, 1080.0f};
	myEngine = nullptr;
}

Terrain::~Terrain()
{
	myPieces.clear();
}

void Terrain::Init(Tga::Engine& aEngine)
{
	myEngine = &aEngine;

	//center Helicopter in middle of screen
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myNextId = 0;
	myCeilingSpawn = -230;
	myFloorSpawn = -230;
	myTimer = 0;
}

void Terrain::Update(float aTimeDelta)
{
	myTimer += aTimeDelta;
	myUpdateTerrainTimer += aTimeDelta;
	myObstacle.timer += aTimeDelta;

	if (myTimer >= 0.32f)
	{
		myTimer = 0.0f;

		const float ID_float = static_cast<float>(myNextId++);
		const int ID_int = static_cast<int>(ID_float);

		float frequency = myTerrainData.frequency * ID_float;
		float amplitude = myTerrainData.amplitude;

		myCeilingSpawn = sin(frequency) * amplitude + myOffset - myGap;
		myPieces.emplace_back(*myEngine, ID_int, myCeilingSpawn, Direction::Up);

		myFloorSpawn = sin(frequency) * amplitude + myOffset - myGap;
		myPieces.emplace_back(*myEngine, ID_int, myFloorSpawn, Direction::Down);
	}

	if (myUpdateTerrainTimer >= myUpdateTerrainDuration)
	{
		myUpdateTerrainTimer = 0;
		UpdateTerrainData();
	}

	if (myObstacle.timer >= myObstacle.timeToSpawn)
	{
		myObstacle.timer = 0;
		myObstacle.timeToSpawn = globalRNG.RangeFloat(myObstacle.obsTimeToSpawnMin, myObstacle.obsTimeToSpawnMax);
		myPieces.emplace_back(*myEngine, -1);
	}

	for (auto it = myPieces.begin(); it != myPieces.end();)
	{
		TerrainPiece& piece = *it;

		piece.Update(aTimeDelta);

		if (!piece.GetIsActive())
		{
			it = myPieces.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Terrain::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	for (const auto& piece : myPieces)
	{
		piece.Render(aSpriteDrawer);
	}
}

void Terrain::ResetTerrain()
{
	myNextId = 0;
	myCeilingSpawn = -230;
	myFloorSpawn = -230;
	myTimer = 0;
	myTerrainData = {14, 100};
	myUpdateTerrainTimer = 0;

	myObstacle.timer = 0;

	for (auto it = myPieces.begin(); it != myPieces.end();)
	{
		it = myPieces.erase(it);
	}
}

void Terrain::StopTerrainMovement()
{
	for (auto piece : myPieces)
	{
		piece.SetSpeed({0.0f, 0.0f});
	}
}

void Terrain::ResumeTerrainMovement()
{
	for (auto piece : myPieces)
	{
		piece.ResetSpeed();
	}
}

void Terrain::UpdateTerrainData()
{
	myGap -= 3;
	myTerrainData.amplitude += 1.0f;
	myTerrainData.frequency += 0.1f;
}


//
//float Terrain::GetRandomSpawn(float aHeight)
//{
//	//aHeight += globalRNG.RangeFloat(-10, 20);
//	myFloorSpawn = CommonUtilities::Clamp(myFloorSpawn, -230.0f, 230.0f);
//}
