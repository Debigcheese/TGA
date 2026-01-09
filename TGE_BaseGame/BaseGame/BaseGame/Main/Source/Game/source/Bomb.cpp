#include "Bomb.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "tge/Engine.h"

Bomb::~Bomb() = default;

void Bomb::OnAdded()
{
	myOwner->SetTexture("Sprites/bomb.png");
	myOwner->SetTransform({
		.position = {myOwner->GetResolution().x / 2.0f, 1110.0f},
		.rotation = 0.0f
	});

	myOwner->SetScale({2.0f, 2.0f});

	auto moveComp = myOwner->GetComponent<MovementComponent>();
	if (!moveComp)
	{
		return;
	}

	moveComp->SetSpeed(170.0f);
	moveComp->SetGravity(1.0f);
}

void Bomb::Update(float aTimeDelta)
{
	if (myOwner->GetPosition().y <= 110.0f)
	{
		if (myOnExplode)
		{
			myOnExplode();
		}
	}
	UNREFERENCED_PARAMETER(aTimeDelta);
}
