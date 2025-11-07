#include "TerrainPiece.h"
#include "Utils.h"
#include "tge/Graphics/TextureResource.h"
#include "CommonUtilities/Random.h"
#include "tge/texture/TextureManager.h"

TerrainPiece::TerrainPiece(Tga::Engine& aEngine, int aId) // for obstacles
{
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myObstacleTextures[0] = aEngine.GetTextureManager().GetTexture("Sprites/Fireball_1.png");
	myObstacleTextures[1] = aEngine.GetTextureManager().GetTexture("Sprites/Fireball_2.png");
	myObstacleTextures[2] = aEngine.GetTextureManager().GetTexture("Sprites/Fireball_3.png");
	myObstacleTextures[3] = aEngine.GetTextureManager().GetTexture("Sprites/Fireball_4.png");
	myObstacleTextures[4] = aEngine.GetTextureManager().GetTexture("Sprites/Fireball_5.png");

	mySharedData.myTexture = myObstacleTextures[0];

	myPosition = {myScreenResolution.x + 100, myScreenResolution.y};

	float offsetY = globalRNG.RangeFloat(-200, 200);
	myPosition.y = myScreenResolution.y / 2 + offsetY;

	mySpriteInstance.myPosition = myPosition;
	mySpriteInstance.myPivot = {0.5f, 0.5f};
	mySpriteInstance.mySize = mySharedData.myTexture->CalculateTextureSize() * Tga::Vector2ui{2, 2};
	mySpriteInstance.myColor = Tga::Color(1, 1, 1, 1);

	myMovement.speed = {-myCameraSpeed * 2, 0.0f};
	mySpriteInstance.myRotation = 91.1f;

	myIsActive = true;
	myId = aId;
}

TerrainPiece::TerrainPiece(Tga::Engine& aEngine, int aId, float aSpawnHeigth, Direction aDirection) // for terrain
{
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myMovement.speed = {-myCameraSpeed, 0.0f};

	myPosition.x = myScreenResolution.x + 100;
	myMovement.direction = aDirection;

	if (aDirection == Direction::Up)
	{
		myPosition.y = myScreenResolution.y;
		mySpriteInstance.myRotation *= -1;
		myPosition.y -= aSpawnHeigth;
	}
	else if (aDirection == Direction::Down)
	{
		myPosition.y = 0;
		myPosition.y += aSpawnHeigth;
	}

	myIsActive = true;
	myId = aId;

	mySharedData.myTexture = aEngine.GetTextureManager().GetTexture(myTerrainTexturePath);
	mySpriteInstance.myPivot = {0.5f, 0.5f};
	mySpriteInstance.mySize = mySharedData.myTexture->CalculateTextureSize() * Tga::Vector2ui{2, 2};
	mySpriteInstance.myColor = Tga::Color(1, 1, 1, 1);
	mySpriteInstance.myPosition = myPosition;
}

TerrainPiece::~TerrainPiece()
{
}

void TerrainPiece::Update(float aTimeDelta)
{
	float desiredPos = myPosition.x + myMovement.speed.x * aTimeDelta;

	if (myPosition.x <= -100)
	{
		myIsActive = false;
	}

	if (myId < 0) // for obstacles
	{
		UpdateAnimation(aTimeDelta);
	}

	myPosition.x = desiredPos;
	mySpriteInstance.myPosition.x = myPosition.x;
}

void TerrainPiece::UpdateAnimation(float aDeltaTime)
{
	myObstacleAnimTimer += aDeltaTime;

	constexpr std::size_t tCount = std::size(myObstacleTextures);
	constexpr float animTime = 0.1f;

	mySharedData.myTexture = myObstacleTextures[static_cast<std::size_t>(myObstacleAnimTimer / animTime) % tCount];
}

void TerrainPiece::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	aSpriteDrawer.Draw(mySharedData, mySpriteInstance);
}

void TerrainPiece::ResetSpeed()
{
	if (myId < 0)
	{
		myMovement.speed = {-myCameraSpeed * 2, 0.0f};
	}
	else
	{
		myMovement.speed = {-myCameraSpeed, 0.0f};
	}
}
