#include "Jet.h"
#include "CommonUtilities/Random.h"
#include "Entity.h"
#include "MovementComponent.h"


Jet::~Jet()
{
}

void Jet::OnAdded()
{
	Component::OnAdded();

	myOwner->SetTexture("Sprites/jet.png");

	Transform transform;
	transform.pivot = {0.5f, 1.0f};
	transform.scale = {1.0f, 1.0f};

	//myType = EnemyType::Jet;

	myLeftSide = static_cast<bool>(globalRNG.RangeInt(0, 1));

	Tga::Vector2f resolution = myOwner->GetResolution();

	auto moveComp = myOwner->GetComponent<MovementComponent>();

	if (myLeftSide)
	{
		transform.position = {0.0f, resolution.y - 110.0f};
		if (moveComp)
		{
			moveComp->SetDirection({1.0f, 0.0f});
		}
	}
	else
	{
		transform.position = {resolution.x, resolution.y - 80.0f};
		if (moveComp)
		{
			moveComp->SetDirection({-1.0f, 0.0f});
		}
		transform.scale.x = -1.0f; // Flip horizontally
	}

	myOwner->SetTransform(transform);
	moveComp->SetSpeed(200.0f);
	moveComp->SetGravity(0.0f);
}

void Jet::Update(float aTimeDelta)
{
	Component::Update(aTimeDelta);

	if (myDropBomb && myOnDropBomb)
	{
		myOnDropBomb(myOwner->GetPosition());
		myJetBombDropped = true;
	}

	if (myJetBombDropped)
	{
		myDropBomb = false;
		return;
	}

	float centerX = myOwner->GetResolution().x / 2;
	Tga::Vector2f position = myOwner->GetPosition(); // Get updated position

	if (position.x <= centerX + 20 && position.x >= centerX - 20)
	{
		myDropBomb = true;
	}
}
