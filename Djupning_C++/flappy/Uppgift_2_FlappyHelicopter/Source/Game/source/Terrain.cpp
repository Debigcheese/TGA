#include "Terrain.h"
#include "Utils.h"
#include "tge/Graphics/TextureResource.h"

Terrain::Terrain()
{
	myMovement.speed = {400.0f, 400.0f};
	myPosition = {0.0f, 0.0f};
	myScreenResolution = {1920.0f, 1080.0f};
}

Terrain::~Terrain()
{
}

void Terrain::Init(Tga::Engine& aEngine)
{
	mySprite.sharedData.myTexture = Utils::GetTextureFromPath(aEngine, mySprite.texturePath);
	//Utils::GetTextureFromPath(aEngine, mySprite.texturePath);

	//center Helicopter in middle of screen
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myPosition = {myScreenResolution.x, myScreenResolution.y / 2};

	mySprite.instance.myPosition = myPosition;
	mySprite.instance.myPivot = {0.5f, 0.5f};
	mySprite.instance.mySize = mySprite.sharedData.myTexture->CalculateTextureSize() / 5;
	mySprite.instance.myColor = Tga::Color(1, 1, 1, 1);

	myBounds.maxX = 0.0f;
	myBounds.minX = myScreenResolution.x - 0.0f;

	myBounds.minY = 0.0f;
	myBounds.maxY = 0.0f;
}

void Terrain::Update(float aTimeDelta)
{
	float desiredPos = myPosition.x + myMovement.speed.x * aTimeDelta;

	if (desiredPos >= myBounds.minX)
	{
		desiredPos = myBounds.minY;
	}

	myPosition.x = desiredPos;
	mySprite.instance.myPosition.x = myPosition.x;
}

void Terrain::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	aSpriteDrawer.Draw(mySprite.sharedData, mySprite.instance);
}

void Terrain::SetPosition(float aHeight, int aDirection)
{
	if (aDirection < 0)
	{
		myPosition.y = myBounds.maxY;
		myPosition.y -= aHeight;
	}
	else if (aDirection >= 0)
	{
		myPosition.y = myBounds.minY;
		myPosition.y += aHeight;
	}

	mySprite.instance.myPosition = myPosition;
}
