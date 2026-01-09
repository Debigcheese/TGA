#include "Paddle.h"
#include "tge/texture/TextureManager.h"

Paddle::Paddle()
{
	mySpeed = {500.0f, 500.0f};
	myPosition = {0.0f, 0.0f};
	myScreenResolution = {1920.0f, 1080.0f};
}

Paddle::~Paddle()
{
}

void Paddle::Init(Tga::Engine& aEngine, Actor aActor)
{
	//load sprite
	mySharedData.myTexture = GetTexture(aEngine, aActor);

	//center Paddle in middle of screen
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	//position Paddle
	myPosition = {myScreenResolution.x - 50.0f, 200};
	mySpriteInstance.myPosition = myPosition;

	myBounds.maxY = 45.0f;
	myBounds.minY = myScreenResolution.y - 45.0f;

	SetDirection({0, -1});
	//set pivot
	mySpriteInstance.myPivot = {0.5f, 0.5f};
	//change size
	mySpriteInstance.mySize = mySharedData.myTexture->CalculateTextureSize() / 7;
	//change color
	mySpriteInstance.myColor = Tga::Color(1, 1, 1, 1);
	//mySpriteInstance.myColor = Tga::Color{0.3f, 0.8f, 0.8f, 0.2f};
}

void Paddle::Update(float aTimeDelta)
{
	const float dy = myDirection.y * mySpeed.y * aTimeDelta;

	float desiredPos = myPosition.y + dy;

	if (desiredPos >= myBounds.minY)
	{
		desiredPos = myBounds.minY;
	}
	else if (desiredPos <= myBounds.maxY)
	{
		desiredPos = myBounds.maxY;
	}

	myPosition.y = desiredPos;
	mySpriteInstance.myPosition.y = myPosition.y;
}

void Paddle::SetDirection(Tga::Vector2f aDirection)
{
	myDirection = aDirection;
}

void Paddle::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	if (!myIsVisible)
	{
		return;
	}
	aSpriteDrawer.Draw(mySharedData, mySpriteInstance);
}

void Paddle::SetPosition(Tga::Vector2f aPosition)
{
	myPosition = aPosition;
	mySpriteInstance.myPosition = myPosition;
}

Tga::Vector2f Paddle::GetPosition() const
{
	return myPosition;
}

Tga::Vector2f Paddle::GetSize() const
{
	return mySpriteInstance.mySize;
}

Tga::TextureResource* Paddle::GetTexture(Tga::Engine& aEngine, Actor aActor) const
{
	switch (aActor)
	{
		case Actor::Player:
			{
				return aEngine.GetTextureManager().GetTexture(("Sprites/iceblock.png"));
			}
		case Actor::Enemy:
			{
				return aEngine.GetTextureManager().GetTexture(("Sprites/fireblock.png"));
			}
		default:
			{
				return aEngine.GetTextureManager().GetTexture(("Sprites/Paddle.png"));
			}
	}
}
