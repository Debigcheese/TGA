#include "TerrainPiece.h"
#include "Terrain.h"
#include "Utils.h"
#include "tge/Graphics/TextureResource.h"

TerrainPiece::TerrainPiece()
{
	myMovement.speed = {-400.0f, 400.0f};
	myPosition = {0.0f, 0.0f};
	myScreenResolution = {1920.0f, 1080.0f};
}

TerrainPiece::~TerrainPiece()
{
}

void TerrainPiece::Init(Tga::Engine& aEngine)
{
	mySprite.sharedData.myTexture = Utils::GetTextureFromPath(aEngine, mySprite.texturePath);

	//center Helicopter in middle of screen
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myPosition = {myScreenResolution.x, myScreenResolution.y / 2};

	mySprite.instance.myPosition = myPosition;
	mySprite.instance.myPivot = {0.5f, 0.5f};
	mySprite.instance.mySize = mySprite.sharedData.myTexture->CalculateTextureSize() * Tga::Vector2ui{2, 2};
	mySprite.instance.myColor = Tga::Color(1, 1, 1, 1);
}

void TerrainPiece::Update(float aTimeDelta)
{
	float desiredPos = myPosition.x + myMovement.speed.x * aTimeDelta;

	if (myPosition.x <= -100)
	{
		myIsActive = false;
	}

	myPosition.x = desiredPos;
	mySprite.instance.myPosition.x = myPosition.x;
}

void TerrainPiece::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	aSpriteDrawer.Draw(mySprite.sharedData, mySprite.instance);
}

void TerrainPiece::SetSpawn(float aHeight, Direction aDirection)
{
	myPosition.x = myScreenResolution.x + 100;
	myIsActive = true;
	myDirection = aDirection;

	if (aDirection == Direction::Up)
	{
		myPosition.y = myScreenResolution.y;
		mySprite.instance.myRotation *= -1;
		myPosition.y -= aHeight;
	}
	else if (aDirection == Direction::Down)
	{
		myPosition.y = 0;
		myPosition.y += aHeight;
	}

	mySprite.instance.myPosition = myPosition;
}
