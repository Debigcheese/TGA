#include "Terrain.h"
#include "Utils.h"
#include "CommonUtilities/Random.h"
#include "CommonUtilities/UtilityFunctions.h"

Terrain::Terrain()
{
	myScreenResolution = {1920.0f, 1080.0f};
	myEngine = nullptr;
}

Terrain::~Terrain()
{
	for (auto* piece : myPieces)
	{
		delete piece;
	}
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

	if (myTimer >= 0.32f)
	{
		myTimer = 0.0f;

		TerrainPiece* upperPiece = new TerrainPiece;
		upperPiece->Init(*myEngine);
		upperPiece->SetId(myNextId++);

		myCeilingSpawn = sin(upperPiece->GetId() * 18.0f) * 100 + offset;
		upperPiece->SetSpawn(myCeilingSpawn, Direction::Up);


		TerrainPiece* lowerPiece = new TerrainPiece;
		lowerPiece->Init(*myEngine);
		lowerPiece->SetId(myNextId++);

		myFloorSpawn = sin(lowerPiece->GetId() * 18.0f) * 100 + offset;
		lowerPiece->SetSpawn(myFloorSpawn, Direction::Down);

		myPieces.emplace_back(upperPiece);
		myPieces.emplace_back(lowerPiece);
	}

	for (auto it = myPieces.begin(); it != myPieces.end();)
	{
		TerrainPiece* piece = *it;

		piece->Update(aTimeDelta);

		if (!piece->GetIsActive())
		{
			delete piece;
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
	for (auto* piece : myPieces)
	{
		piece->Render(aSpriteDrawer);
	}
}

void Terrain::ResetTerrain()
{
	myNextId = 0;
	myCeilingSpawn = -230;
	myFloorSpawn = -230;
	myTimer = 0;

	for (auto it = myPieces.begin(); it != myPieces.end();)
	{
		TerrainPiece* piece = *it;

		delete piece;
		it = myPieces.erase(it);
	}
}

void Terrain::StopTerrainMovement()
{
	for (auto piece : myPieces)
	{
		piece->SetSpeed({0.0f, 0.0f});
	}
}

//
//float Terrain::GetRandomSpawn(float aHeight)
//{
//	//aHeight += globalRNG.RangeFloat(-10, 20);
//	myFloorSpawn = CommonUtilities::Clamp(myFloorSpawn, -230.0f, 230.0f);
//}
