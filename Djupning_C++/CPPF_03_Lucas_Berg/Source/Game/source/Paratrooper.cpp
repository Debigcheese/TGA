#include "Paratrooper.h"
#include "CommonUtilities/Random.h"
#include "tge/texture/TextureManager.h"

Paratrooper::Paratrooper()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	myTextures[0] = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/Trooper.png");
	myTextures[1] = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/Paratrooper.png");
	myTextures[2] = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/TrooperDeath.png");

	mySpriteData.myTexture = myTextures[0];

	mySpriteInstance.myPivot = {0.5f, 1.0f};
	mySpriteInstance.myPosition = {myResolution.x / 2, 110.0f};
	mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
	mySpriteInstance.mySizeMultiplier = 1;

	float forgotParachute = globalRNG.RangeFloat(0, 100);

	if (forgotParachute >= 50)
	{
		myForgotParachuteAtHome = true;
	}

	myDirection = {0.0f, -1.0f};
	mySpeed = 300.0f;

	myType = EnemyType::Paratrooper;
}

Paratrooper::~Paratrooper()
{
}

void Paratrooper::Update(float aTimeDelta)
{
	Enemy::Update(aTimeDelta);


	if (mySpriteInstance.myPosition.x > myResolution.x / 2)
	{
		mySide = Side::Left;
	}
	else
	{
		mySide = Side::Right;
	}

	if (myState == State::Scored)
	{
		return;
	}

	if (myDeathDuration <= 0)
	{
		myState = State::Destroy;
		return;
	}

	if (myState == State::Dead)
	{
		myDeathDuration -= aTimeDelta;
		mySpriteData.myTexture = myTextures[2];
		mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
		return;
	}

	myParachuteTimer += aTimeDelta;
	if (myParachuteTimer >= myTimeToParachute && !myForgotParachuteAtHome)
	{
		myState = State::Parachuting;
		mySpriteData.myTexture = myTextures[1];
		mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
		myParachuteTimer = -100.0f; // temp
	}

	if (mySpriteInstance.myPosition.y <= 45.0f && myState != State::Grounded)
	{
		if (myState == State::Falling)
		{
			myState = State::Dead;
			myLifeState = LifeState::Dead;
			return;
		}

		myState = State::Grounded;
		myDirection.x = myResolution.x / 2 - mySpriteInstance.myPosition.x;

		myDirection.x > 0.0f ? myDirection.x = 1.0f : myDirection.x = -1.0f;

		myDirection.y = 0.0f;
	}

	if (myState == State::Falling || myState == State::Parachuting)
	{
		if (myState == State::Parachuting)
		{
			mySpeed = 100.0f;
		}

		Tga::Vector2f velocity = mySpeed * myDirection * aTimeDelta;
		mySpriteInstance.myPosition += velocity;

		return;
	}

	if (myState == State::Grounded)
	{
		mySpriteData.myTexture = myTextures[0];
		mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
		mySpeed = 300.0f;
		Tga::Vector2f velocity = mySpeed * myDirection * aTimeDelta;
		mySpriteInstance.myPosition += velocity;

		if (HasReachedPlayer() && myState != State::Scored)
		{
			if (myOnReachedPlayer)
			{
				myOnReachedPlayer(this);
			}
		}
	}
}

bool Paratrooper::HasReachedPlayer() const
{
	if (mySpriteInstance.myPosition.x >= myResolution.x / 2 - 40.0f - myDistanceOffset &&
		mySpriteInstance.myPosition.x <= myResolution.x / 2 + 40.0f + myDistanceOffset)
	{
		return true;
	}
	return false;
}

Tga::Vector2f Paratrooper::GetParachutePosition() const
{
	return Tga::Vector2f{mySpriteInstance.myPosition.x, mySpriteInstance.myPosition.y + 50};
}
