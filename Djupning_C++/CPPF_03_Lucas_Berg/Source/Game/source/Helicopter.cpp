#include "Helicopter.h"
#include "tge/texture/TextureManager.h"
#include "CommonUtilities/UtilityFunctions.h"
#include "Config.h"

Helicopter::Helicopter()
{
	myMovement.velocity = {0.0f, 0.0f};
	myMovement.accelerationTime = 0.0f;
	myMovement.direction = Direction::None;
	myScreenResolution = {1920.0f, 1080.0f};
}

Helicopter::~Helicopter()
{
}

void Helicopter::Init(Tga::Engine& aEngine, GameState* aGameState)
{
	float gravity = Config::Get()["HelicopterData"]["Gravity"];
	float flyPower = Config::Get()["HelicopterData"]["FlyPower"];

	myGravity = gravity;
	myMovement.flyPower = flyPower;

	for (int i = 0; i < std::size(myTextures); ++i)
	{
		std::string path = "Sprites/Helicopter_" + std::to_string(i + 1) + ".png";
		myTextures[i] = aEngine.GetTextureManager().GetTexture(path.c_str());
	}

	mySprite.sharedData.myTexture = myTextures[0];

	for (int i = 0; i < std::size(myBloodTextures); ++i)
	{
		std::string path = "Sprites/Blood/1_" + std::to_string(i) + ".png";
		myBloodTextures[i] = aEngine.GetTextureManager().GetTexture(path.c_str());
	}

	myGameState = aGameState;

	//center Helicopter in middle of screen
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myPosition = {300, myScreenResolution.y / 2};
	mySpawnPosition = myPosition;

	myDefaultRotation = mySprite.instance.myRotation;

	mySprite.instance.myPosition = myPosition;
	mySprite.instance.myPivot = {0.5f, 0.5f};
	mySprite.instance.myColor = Tga::Color(1, 1, 1, 1);

	myDefaultSize = mySprite.sharedData.myTexture->CalculateTextureSize() * Tga::Vector2ui{2, 2};
	myDeathSize = mySprite.sharedData.myTexture->CalculateTextureSize() * Tga::Vector2ui{5, 5};
	mySprite.instance.mySize = myDefaultSize;

	myBounds.maxY = 45.0f;
	myBounds.minY = myScreenResolution.y - 45.0f;
}

void Helicopter::Update(float aTimeDelta)
{
	if (myState == State::Dead)
	{
		return;
	}
	if (myState == State::Dying)
	{
		myDeathAnimTimer += aTimeDelta;
		UpdateAnimation(aTimeDelta, myBloodTextures, std::size(myBloodTextures));
		mySprite.instance.mySize = myDeathSize;
		if (myDeathAnimTimer >= 2.2f)
		{
			myState = State::Dead;
		}
		return;
	}

	UpdateAnimation(aTimeDelta, myTextures, std::size(myTextures));

	if (!myGameState->HasGameStarted())
	{
		return;
	}

	myMovement.velocity.y = GetVelocity(aTimeDelta);
	mySprite.instance.myRotation = GetRotation(aTimeDelta);

	float desiredPos = CheckBounds(aTimeDelta);

	myPosition.y = desiredPos;
	mySprite.instance.myPosition.y = myPosition.y;
}


void Helicopter::Render(Tga::SpriteDrawer& aSpriteDrawer) const
{
	if (myState == State::Dead)
	{
		return;
	}

	aSpriteDrawer.Draw(mySprite.sharedData, mySprite.instance);
}

void Helicopter::Reset()
{
	myPosition = mySpawnPosition;
	mySprite.instance.myPosition = myPosition;

	myMovement.velocity = {0.0f, 0.0f};
	myMovement.accelerationTime = 0.0f;
	myMovement.direction = Direction::None;

	myAnimTimer = 0.0f;
	myRotationTimer = 0.0f;
	myDeathAnimTimer = 0.0f;
	myState = State::Alive;
	mySprite.instance.mySize = myDefaultSize;
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

void Helicopter::OnDeath()
{
	myIsDead = true;
	myState = State::Dying;
}

void Helicopter::UpdateAnimation(float aDeltaTime, Tga::TextureResource* aTextures[], size_t aFrames)
{
	myAnimTimer += aDeltaTime;

	constexpr float animTime = 0.1f;

	mySprite.sharedData.myTexture = aTextures[static_cast<std::size_t>(myAnimTimer / animTime) % aFrames];
}

float Helicopter::GetVelocity(float aTimeDelta)
{
	myMovement.accelerationTime = CommonUtilities::Clamp(
		myMovement.accelerationTime + aTimeDelta, 0.5f, 1.0f);

	const auto speed = myMovement.flyPower;
	const float dir = static_cast<float>(myMovement.direction);
	float velocity = myMovement.velocity.y;

	velocity += speed * dir * myMovement.accelerationTime * aTimeDelta;
	velocity -= myGravity * aTimeDelta;

	return velocity;
}

float Helicopter::GetRotation(float aDeltaTime)
{
	myRotationTimer += aDeltaTime / 50;
	myRotationTimer = CommonUtilities::Clamp(myRotationTimer, 0.0f, 1.0f);

	const float currentRot = mySprite.instance.myRotation;
	const float targetRot = static_cast<float>(myMovement.direction) * 0.75f;

	float lerpValue = CommonUtilities::Lerp(currentRot, targetRot, myRotationTimer);

	const float rotation = CommonUtilities::Clamp(lerpValue, -10.0f, 25.0f);

	return rotation;
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
