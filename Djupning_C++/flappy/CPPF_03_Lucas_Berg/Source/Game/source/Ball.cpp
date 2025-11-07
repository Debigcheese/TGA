#include "Ball.h"
#include "tge/texture/TextureManager.h"
#include <cmath>
#include "CommonUtilities/Random.h"

Ball::Ball()
{
	mySpeed = {500.0f, 500.0f};
	myPosition = {0.0f, 0.0f};
	myScreenResolution = {1920.0f, 1080.0f};
	myDirection = {-1.0f, -1.0f};
	myStartingSpeed = mySpeed;
}

Ball::~Ball()
{
}

void Ball::Init(Tga::Engine& aEngine)
{
	mySharedData.myTexture = aEngine.GetTextureManager().GetTexture(("Sprites/FireBall.png"));

	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myStartingPosition = Tga::Vector2f{0.5f, 0.5f} * myScreenResolution;
	myPosition = myStartingPosition;
	mySpriteInstance.myPosition = myPosition;

	SetRandomPos();
	SetRandomDirection();

	mySpriteInstance.myPivot = {0.5f, 0.5f};
	mySpriteInstance.mySize = mySharedData.myTexture->CalculateTextureSize() / 10;
	mySpriteInstance.myColor = Tga::Color(1, 1, 1, 1);
}

void Ball::Update(float aTimeDelta)
{
	myTimeToSpawn -= aTimeDelta;
	if (myTimeToSpawn > 0.0f)
	{
		return;
	}

	myVelocity.x = mySpeed.x * myDirection.x;
	myVelocity.y = mySpeed.y * myDirection.y;

	myPosition.x += myVelocity.x * aTimeDelta;
	myPosition.y += myVelocity.y * aTimeDelta;

	if (myPosition.y > (myScreenResolution.y - 10.0f))
	{
		myDirection.y = -1.0f;
	}
	else if (myPosition.y < 10)
	{
		myDirection.y = 1.0f;
	}

	Tga::Vector2f direction = myVelocity;

	float angleRad = std::atan2(direction.y, direction.x);

	if (angleRad < 0.0f)
	{
		angleRad += 3.14f * 2.0f;
	}

	mySpriteInstance.myRotation = angleRad;
	mySpriteInstance.myPosition = myPosition;
}

void Ball::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	if (!myIsVisible)
	{
		return;
	}
	aSpriteDrawer.Draw(mySharedData, mySpriteInstance);
}

void Ball::Disable()
{
	mySpeed = {0.0f, 0.0f};
	SetVisibility(false);
}

void Ball::Reset()
{
	SetVisibility(true);
	myPosition = myStartingPosition;
	mySpeed = myStartingSpeed;
	myBounceCounter = 0;
	SetRandomPos();
	SetRandomDirection();
}

void Ball::SetRandomPos()
{
	const float random = globalRNG.RangeFloat(0.2f, 1.8f);
	myPosition.y = myStartingPosition.y * random;
	mySpriteInstance.myPosition = myPosition;
}

void Ball::SetRandomDirection()
{
	const int random = globalRNG.RangeInt(0, 1);

	if (random <= 0)
	{
		myDirection.x = -1.0f;
	}
	else
	{
		myDirection.x = 1.0f;
	}
}

void Ball::SwitchDirection()
{
	myDirection.x = -myDirection.x;
}

bool Ball::CheckCollision(Tga::Vector2f aPosition, Tga::Vector2f aSize) const
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

void Ball::ResolveCollision(const Tga::Vector2f& aPosition, const Tga::Vector2f& aColliderSize)
{
	Tga::Vector2f halfSizeA = {aColliderSize.x / 2, aColliderSize.y / 2};
	Tga::Vector2f halfSizeB = {GetSize().x / 2, GetSize().y / 2};

	Tga::Vector2f centerA = aPosition;
	Tga::Vector2f centerB = myPosition;

	float overlapX = (halfSizeA.x + halfSizeB.x) - std::fabs(centerA.x - centerB.x);
	float overlapY = (halfSizeA.y + halfSizeB.y) - std::fabs(centerA.y - centerB.y);

	// Only resolve if overlapping
	if (overlapX > 0 && overlapY > 0)
	{
		// Move out along the axis of least penetration
		if (overlapX < overlapY)
		{
			if (centerB.x < centerA.x)
			{
				myPosition.x = centerA.x - (halfSizeA.x + halfSizeB.x);
			}
			else
			{
				myPosition.x = centerA.x + (halfSizeA.x + halfSizeB.x);
			}
		}
		else
		{
			if (centerB.y < centerA.y)
			{
				myPosition.y = centerA.y - (halfSizeA.y + halfSizeB.y);
			}
			else
			{
				myPosition.y = centerA.y + (halfSizeA.y + halfSizeB.y);
			}
		}
		// Update sprite position as well
		mySpriteInstance.myPosition = myPosition;
	}
}

void Ball::Bounce()
{
	myBounceCounter++;

	mySpeed.x *= 1.05f;
	mySpeed.y *= 1.05f;
}
