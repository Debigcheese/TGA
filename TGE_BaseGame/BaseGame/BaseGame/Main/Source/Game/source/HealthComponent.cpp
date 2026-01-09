#include "HealthComponent.h"

#include "Entity.h"
#include "MovementComponent.h"
#include "tge/Engine.h"
#include "tge/texture/TextureManager.h"


HealthComponent::HealthComponent()
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::OnAdded()
{
	Component::OnAdded();
	myHealthState = HealthState::Alive;

	Tga::Engine& engine = *Tga::Engine::GetInstance();

	for (int i = 0; i < DEATH_TEXTURE_SIZE; ++i)
	{
		std::string texturePath = "Sprites/explosion_" + std::to_string(i + 1) + ".png";
		myDeathTextures[i] = engine.GetTextureManager().GetTexture(texturePath.c_str());
	}
}

void HealthComponent::Update(float aDeltaTime)
{
	Component::Update(aDeltaTime);

	if (myHealthState == HealthState::Dead)
	{
		UpdateDeathAnimation(aDeltaTime);
	}
	if (myTimeBeforeDestroy >= 1.0f)
	{
		myHealthState = HealthState::Destroy;
	}
}

void HealthComponent::OnTakeDamage(int aDamage)
{
	if (myHealthState != HealthState::Alive)
	{
		return;
	}

	if (aDamage >= myHealthPoints)
	{
		OnDeath();
	}
	else
	{
		myHealthPoints -= aDamage;
	}
}

void HealthComponent::OnDeath()
{
	myHealthPoints = 0;
	myHealthState = HealthState::Dead;

	if (myOnDeath)
	{
		myOnDeath(myOwner);
	}

	myOwner->SetTexture(myDeathTextures[0]);
	myOwner->SetScale(1.0f);
	myOwner->RemoveComponent<MovementComponent>();
}

void HealthComponent::UpdateDeathAnimation(float aDeltaTime)
{
	myTimeBeforeDestroy += aDeltaTime;
	myOwner->SetTexture(myDeathTextures[static_cast<int>(myTimeBeforeDestroy * 4) % DEATH_TEXTURE_SIZE]);
}
