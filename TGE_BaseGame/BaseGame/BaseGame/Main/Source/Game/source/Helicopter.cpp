#include "Helicopter.h"

#include "Entity.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "CommonUtilities/Random.h"
#include "tge/Engine.h"
#include "tge/texture/TextureManager.h"


Helicopter::~Helicopter()
{
}

void Helicopter::OnAdded()
{
	Component::OnAdded();

	Tga::Engine& engine = *Tga::Engine::GetInstance();

	for (int i = 0; i < TEXTURE_SIZE_CHOPPER; ++i)
	{
		std::string texturePath = "Sprites/chopper_" + std::to_string(i + 1) + ".png";
		myTexturesChopper[i] = engine.GetTextureManager().GetTexture(texturePath.c_str());
	}
	myOwner->SetTexture(myTexturesChopper[0]);
	myOwner->SetScale({1.0, 1.0f});

	//myType = EnemyType::Helicopter;
	myLeftSide = static_cast<bool>(globalRNG.RangeInt(0, 1));
	const Tga::Vector2f resolution = myOwner->GetResolution();

	auto moveComp = myOwner->GetComponent<MovementComponent>();

	if (myLeftSide)
	{
		myOwner->SetPosition({0.0f, resolution.y - 110.0f});
		if (moveComp)
		{
			moveComp->SetDirection({1.0f, 0.0f});
		}
	}
	else
	{
		myOwner->SetPosition({resolution.x, resolution.y - 80.0f});
		if (moveComp)
		{
			moveComp->SetDirection({-1.0f, 0.0f});
		}
		myOwner->SetScale({-1.0, 1.0f});
	}

	if (moveComp)
	{
		moveComp->SetGravity(0.0f);
		moveComp->SetSpeed(100.0f);
	}

	float spawnChance = globalRNG.RangeFloat(0.0f, 100.0f);

	if (spawnChance <= 20)
	{
		mySpawnTrooper = SpawnTrooper::NeverSpawn;
		return;
	}

	myTimeBeforeParatrooper = globalRNG.RangeFloat(2.0f, 4.0f);
}

void Helicopter::Update(float aTimeDelta)
{
	//Enemy::Update(aTimeDelta);

	UpdateAnimation(aTimeDelta);

	myTimeBeforeParatrooper -= aTimeDelta;

	if (myTimeBeforeParatrooper <= 0 && mySpawnTrooper != SpawnTrooper::NeverSpawn)
	{
		mySpawnTrooper = SpawnTrooper::ShouldSpawn;
		myTimeBeforeParatrooper = 100.0f;
	}

	if (mySpawnTrooper == ShouldSpawn && myOnSpawnTrooper)
	{
		myOnSpawnTrooper(myOwner->GetPosition());
		mySpawnTrooper = HasSpawned;
	}
}

void Helicopter::UpdateAnimation(float aTimeDelta)
{
	//if (myLifeState == LifeState::Dead)
	//{
	//	return;
	//}
	if (myOwner->GetComponent<HealthComponent>()->GetHealthState() == HealthState::Alive)
	{
		myAnimTimerChopper += aTimeDelta;
		myOwner->SetTexture(myTexturesChopper[static_cast<int>(myAnimTimerChopper * 10) % TEXTURE_SIZE_CHOPPER]);
	}
}
