#include "Paratrooper.h"

#include "Entity.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "ParachuteComponent.h"
#include "CommonUtilities/Random.h"
#include "tge/texture/TextureManager.h"

Paratrooper::~Paratrooper()
{
}

void Paratrooper::OnAdded()
{
	Component::OnAdded();

	Tga::Engine& engine = *Tga::Engine::GetInstance();

	myTextures[0] = engine.GetTextureManager().GetTexture("Sprites/Trooper.png");
	myTextures[1] = engine.GetTextureManager().GetTexture("Sprites/Paratrooper.png");
	myTextures[2] = engine.GetTextureManager().GetTexture("Sprites/FallToDeath.png");

	myOwner->SetTexture(myTextures[0]);

	float forgotParachute = globalRNG.RangeFloat(0, 100);
	if (forgotParachute >= 50)
	{
		myForgotParachuteAtHome = true;
	}

	myMovementComp = myOwner->GetComponent<MovementComponent>();

	if (myMovementComp)
	{
		myMovementComp->SetVelocityBasedRotation(false);

		myMovementComp->SetDirection({0.0f, -1.0});
		myMovementComp->SetGravity(1.0f);
		myMovementComp->SetSpeed(300.0f);
	}
	myOwner->SetScale({1.0f, 1.0f});
}

void Paratrooper::Update(float aTimeDelta)
{
	if (!myMovementComp)
	{
		std::cout << "Paratrooper: No movement comp";
		return;
	}

	Tga::Vector2f position = myOwner->GetPosition();
	Tga::Vector2f resolution = myOwner->GetResolution();

	if (position.x > resolution.x / 2)
	{
		myLeftSide = true;
	}
	else
	{
		myLeftSide = false;
	}

	if (myState == State::Scored)
	{
		return;
	}

	if (myDeathDuration <= 0)
	{
		SetParachuteDestroyed();
		myState = State::Destroy;
		return;
	}

	if (myState == State::Dead)
	{
		myDeathDuration -= aTimeDelta;
		myOwner->SetTexture(myTextures[2]);
		myOwner->SetScale({1.0f, 1.0f});

		if (myMovementComp)
		{
			myMovementComp->SetGravity(0.0f);
			myMovementComp->SetSpeed(0.0f);
		}

		SetParachuteDestroyed();
		return;
	}

	myParachuteTimer += aTimeDelta;
	if (myParachuteTimer >= myTimeToParachute && !myForgotParachuteAtHome)
	{
		myState = State::Parachuting;
		myOwner->SetTexture(myTextures[1]);
		myOwner->SetScale({1.0f, 1.0f});
		myParachuteTimer = -100.0f;

		if (myMovementComp)
		{
			myMovementComp->SetSpeed(100.0f);
		}

		if (myOnParachuteCallback)
		{
			myOnParachuteCallback(myOwner);
		}
	}


	if (position.y <= 45.0f && myState != State::Grounded)
	{
		if (myState == State::Falling)
		{
			myState = State::Dead;
			return;
		}

		SetParachuteDestroyed();

		if (myState == State::Falling)
		{
			myState = State::Grounded;
		}

		float directionX = resolution.x / 2 - position.x;
		directionX = directionX > 0.0f ? 1.0f : -1.0f;

		if (myMovementComp)
		{
			myMovementComp->SetDirection({directionX, 0.0f});
			myMovementComp->SetGravity(0.0f);
		}

		//if (myOnLandedCallback)
		//{
		//	myOnLandedCallback(myOwner);
		//}
	}

	if (myState == State::Falling)
	{
		if (myMovementComp)
		{
			myMovementComp->SetSpeed(300.0f);
			myMovementComp->SetGravity(1.0f);
		}
		myOwner->SetTexture(myTextures[0]);
		myOwner->SetScale({1.0f, 1.0f});
		return;
	}

	if (myState == State::Grounded)
	{
		myOwner->SetTexture(myTextures[0]);
		myOwner->SetScale({1.0f, 1.0f});

		if (myMovementComp)
		{
			myMovementComp->SetSpeed(150.0f);

			if (HasReachedPlayer() && myState != State::Scored)
			{
				myMovementComp->SetDirection({0.0f, 0.0f});
				if (myOnReachedPlayer)
				{
					myOnReachedPlayer(this);
				}
			}
		}
	}
}

void Paratrooper::SetParachuteDestroyed()
{
	if (myParachute)
	{
		Entity* parachute = myParachute;
		myParachute = nullptr;

		if (auto health = parachute->GetComponent<HealthComponent>())
		{
			health->OnTakeDamage(1);
		}
	}

	if (myState != State::Grounded && myState != State::Dead)
	{
		myState = State::Falling;

		if (myMovementComp)
		{
			myMovementComp->SetSpeed(300.0f);
			myMovementComp->SetGravity(1.0f);
		}
	}
}


bool Paratrooper::HasLanded() const
{
	if (myOwner->GetPosition().y <= 46.0f)
	{
		return true;
	}
	return false;
}

bool Paratrooper::HasReachedPlayer() const
{
	Tga::Vector2f position = myOwner->GetPosition();
	Tga::Vector2f resolution = myOwner->GetResolution();

	float centerX = resolution.x / 2;

	if (position.x >= centerX - 40.0f - myDistanceOffset &&
		position.x <= centerX + 40.0f + myDistanceOffset)
	{
		return true;
	}
	return false;
}
