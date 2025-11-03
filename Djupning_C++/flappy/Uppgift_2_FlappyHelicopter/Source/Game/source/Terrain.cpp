#include "Terrain.h"
#include "Utils.h"
#include "tge/Graphics/TextureResource.h"

Terrain::Terrain()
{
	myMovement.speed = {400.0f, 400.0f};
	myPosition = {0.0f, 0.0f};
	myScreenResolution = {1920.0f, 1080.0f};
	myEngine = nullptr;
}

Terrain::~Terrain()
{
}

void Terrain::Init(Tga::Engine& aEngine)
{
	myEngine = &aEngine;
	mySprite.sharedData.myTexture = Utils::GetTextureFromPath(aEngine, mySprite.texturePath);

	//center Helicopter in middle of screen
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

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
		upperPiece->SetSpawn(50, Direction::Up);

		TerrainPiece* lowerPiece = new TerrainPiece;
		lowerPiece->Init(*myEngine);
		lowerPiece->SetSpawn(50, Direction::Down);

		myPieces.push_back(upperPiece);
		myPieces.push_back(lowerPiece);
	}
	for (auto* piece : myPieces)
	{
		piece->Update(aTimeDelta);

		if (!piece->GetIsActive())
		{
			piece->Init(*myEngine);
			if (piece->GetDirection() == Direction::Up)
			{
				piece->SetSpawn(50, Direction::Up);
			}
			else
			{
				piece->SetSpawn(50, Direction::Down);
			}
		}
	}
}

void Terrain::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	for (auto* piece : myPieces)
	{
		piece->Render(aSpriteDrawer);
	}
	aSpriteDrawer.Draw(mySprite.sharedData, mySprite.instance);
}
