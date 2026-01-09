#include "ParachuteComponent.h"

#include "Entity.h"
#include "HealthComponent.h"
#include "MovementComponent.h"

ParachuteComponent::ParachuteComponent()
{
}


void ParachuteComponent::OnAdded()
{
	Component::OnAdded();

	myOwner->SetTexture("Sprites/Particle.png");
	myOwner->SetScale({8.0f, 8.0f});

	myHealthComponent = myOwner->GetComponent<HealthComponent>();
	if (myHealthComponent)
	{
		myHealthComponent->SetOnDeath([this](const Entity* aEntity)
		{
			UNREFERENCED_PARAMETER(aEntity);

			// When parachute is destroyed, make trooper fall
			if (myEntityTrooper)
			{
				auto trooperComp = myEntityTrooper->GetComponent<Paratrooper>();
				if (trooperComp && trooperComp->GetState() == State::Parachuting)
				{
					trooperComp->SetParachuteDestroyed();
				}
			}
		});
	}
}

void ParachuteComponent::Update(float aDeltaTime)
{
	Component::Update(aDeltaTime);
}

void ParachuteComponent::SetParachuteTrooper(Entity* aParatrooper)
{
	myEntityTrooper = aParatrooper;

	//auto trooperHealthComp = myEntityTrooper->GetComponent<HealthComponent>();
	//trooperHealthComp->SetOnDeath([this](const Entity* aEntity)
	//{
	//	if (myHealthComponent)
	//	{
	//		myHealthComponent->OnTakeDamage(1); // REMOVE CHUTE when TROOPER DIES
	//	}
	//	UNREFERENCED_PARAMETER(aEntity);
	//});

	//auto trooper = myEntityTrooper->GetComponent<Paratrooper>();
	//trooper->SetOnLanded([this](const Entity* aEntity)
	//{
	//	if (myHealthComponent)
	//	{
	//		myHealthComponent->OnTakeDamage(1); // REMOVE CHUTE IF LANDING WITHOUT CHUTE
	//	}
	//	UNREFERENCED_PARAMETER(aEntity);
	//});
}
