#include "Helicopter.h"
#include "Paddle.h"
#include "tge/texture/TextureManager.h"
#include "Utils.h"
#include "CommonUtilities/UtilityFunctions.h"

Helicopter::Helicopter()
{
	myMovement.speed = {400.0f, 400.0f};
	myPosition = {0.0f, 0.0f};
	myScreenResolution = {1920.0f, 1080.0f};
}

Helicopter::~Helicopter()
{
}

void Helicopter::Init(Tga::Engine& aEngine)
{
	mySprite.sharedData.myTexture = Utils::GetTextureFromPath(aEngine, mySprite.texturePath);
	//Utils::GetTextureFromPath(aEngine, mySprite.texturePath);

	//center Helicopter in middle of screen
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myPosition = {300, myScreenResolution.y / 2};

	mySprite.instance.myPosition = myPosition;
	mySprite.instance.myPivot = {0.5f, 0.5f};
	mySprite.instance.mySize = mySprite.sharedData.myTexture->CalculateTextureSize() / 7;
	mySprite.instance.myColor = Tga::Color(1, 1, 1, 1);

	myBounds.maxY = 45.0f;
	myBounds.minY = myScreenResolution.y - 45.0f;

	SetVisibility(true);
}

void Helicopter::Update(float aTimeDelta)
{
	float velocity = GetVelocity(aTimeDelta, Direction::Down);

	if (myJumpData.isJumping)
	{
		velocity = GetVelocity(aTimeDelta, Direction::Up);
	}

	myPosition.y = velocity;
	mySprite.instance.myPosition.y = myPosition.y;
}

void Helicopter::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	if (!myIsVisible)
	{
		return;
	}
	aSpriteDrawer.Draw(mySprite.sharedData, mySprite.instance);
}

void Helicopter::SetDirection(Tga::Vector2f aDirection)
{
	if (myMovement.direction != aDirection)
	{
		myMovement.direction = aDirection;
		myMovement.accelerationTime = 0;
	}
}

void Helicopter::SetPosition(Tga::Vector2f aPosition)
{
	myPosition = aPosition;
	mySprite.instance.myPosition = myPosition;
}

float Helicopter::GetVelocity(float aTimeDelta, Direction aDirection)
{
	float dy = 0;

	float acceleration = myMovement.accelerationTime;
	Tga::Vector2f direction = myMovement.direction;
	Tga::Vector2f speed = myMovement.speed;

	acceleration += aTimeDelta;

	if (acceleration >= 1.0f)
	{
		acceleration = 1.0f;
	}

	if (aDirection == Direction::Down)
	{
		dy = speed.y * direction.y * aTimeDelta * acceleration;
	}
	else if (aDirection == Direction::Up)
	{
		dy = speed.y * direction.y * aTimeDelta * acceleration;
	}

	float desiredPos = myPosition.y + dy;

	if (desiredPos >= myBounds.minY)
	{
		desiredPos = myBounds.minY;
	}
	else if (desiredPos <= myBounds.maxY)
	{
		desiredPos = myBounds.maxY;
	}
	return desiredPos;
}

bool Helicopter::CheckCollision(Tga::Vector2f aPosition, Tga::Vector2f aSize) const
{
	// AABB vs AABB
	// half size -> pivot in middle
	const Tga::Vector2f sizeHalfA = {aSize.x / 2, aSize.y / 2,};
	const Tga::Vector2f sizeHalfB = {GetSize().x / 2, GetSize().y / 2,};

	//distance between centers
	const float dx = std::fabs(myPosition.x - aPosition.x);
	const float dy = std::fabs(myPosition.y - aPosition.y);

	//compare distances with combined half sizes
	return (dx <= (sizeHalfA.x + sizeHalfB.x)) && (dy <= (sizeHalfA.y + sizeHalfB.y));
}
