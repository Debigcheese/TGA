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
	myTextures[0] = Utils::GetTextureFromPath(aEngine, "Sprites/Helicopter_1.png");
	myTextures[1] = Utils::GetTextureFromPath(aEngine, "Sprites/Helicopter_2.png");
	myTextures[2] = Utils::GetTextureFromPath(aEngine, "Sprites/Helicopter_3.png");

	mySprite.sharedData.myTexture = myTextures[0];
	//Utils::GetTextureFromPath(aEngine, mySprite.texturePath);

	//center Helicopter in middle of screen
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myPosition = {300, myScreenResolution.y / 2};
	mySpawnPosition = myPosition;

	myDefaultRotation = mySprite.instance.myRotation;

	mySprite.instance.myPosition = myPosition;
	mySprite.instance.myPivot = {0.5f, 0.5f};
	mySprite.instance.mySize = mySprite.sharedData.myTexture->CalculateTextureSize() * Tga::Vector2ui{2, 2};
	mySprite.instance.myColor = Tga::Color(1, 1, 1, 1);

	myBounds.maxY = 45.0f;
	myBounds.minY = myScreenResolution.y - 45.0f;

	SetActive(true);
}

void Helicopter::Update(float aTimeDelta)
{
	if (!myIsActive)
	{
		return;
	}

	UpdateAnimation(aTimeDelta);

	CalculateVelocity(aTimeDelta);

	myRotationTimer += aTimeDelta / 50;
	myRotationTimer = CommonUtilities::Clamp(myRotationTimer, 0.0f, 1.0f);

	float lerpValue = CommonUtilities::Lerp(mySprite.instance.myRotation,
	                                        static_cast<float>(myMovement.direction) * 0.75f,
	                                        myRotationTimer);

	mySprite.instance.myRotation = CommonUtilities::Clamp(
		lerpValue,
		-10.0f,
		25.0f);

	float desiredPos = CheckBounds(aTimeDelta);

	myPosition.y = desiredPos;
	mySprite.instance.myPosition.y = myPosition.y;
}

void Helicopter::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	if (!myIsActive)
	{
		return;
	}
	aSpriteDrawer.Draw(mySprite.sharedData, mySprite.instance);
}

void Helicopter::Reset()
{
	myPosition = mySpawnPosition;
	mySprite.instance.myPosition = myPosition;
	myMovement.velocity = 0;
	myMovement.accelerationTime = 0;
}

void Helicopter::SetDirection(Direction aDirection)
{
	if (myMovement.direction != aDirection)
	{
		myMovement.direction = aDirection;
		myMovement.accelerationTime = 0.5f;
		myRotationTimer = 0;
	}
}

void Helicopter::SetPosition(Tga::Vector2f aPosition)
{
	myPosition = aPosition;
	mySprite.instance.myPosition = myPosition;
}

void Helicopter::UpdateAnimation(float aDeltaTime)
{
	myAnimTimer += aDeltaTime;

	if (myAnimTimer < 0.1f)
	{
		mySprite.sharedData.myTexture = myTextures[0];
	}
	else if (myAnimTimer > 0.1f && myAnimTimer < 0.2f)
	{
		mySprite.sharedData.myTexture = myTextures[1];
	}
	else if (myAnimTimer <= 0.3f)
	{
		mySprite.sharedData.myTexture = myTextures[2];
	}
	else
	{
		myAnimTimer = 0.0f;
	}
}

float Helicopter::CalculateVelocity(float aTimeDelta)
{
	Tga::Vector2f speed = myMovement.speed;

	myMovement.accelerationTime = CommonUtilities::Clamp(
		myMovement.accelerationTime + aTimeDelta, 0.5f, 1.0f);

	float dir = static_cast<float>(myMovement.direction);

	myMovement.velocity.y += speed.y * dir * myMovement.accelerationTime * aTimeDelta;

	return myMovement.velocity.y;
}

float Helicopter::CheckBounds(float aTimeDelta)
{
	float desiredPos = myPosition.y + myMovement.velocity.y * aTimeDelta;

	if (desiredPos >= myBounds.minY)
	{
		myMovement.velocity = 0;
		desiredPos = myBounds.minY;
	}
	else if (desiredPos <= myBounds.maxY)
	{
		myMovement.velocity = 0;
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
