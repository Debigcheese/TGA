#include "EnemySpawner.h"
#include "Jet.h"
#include "Helicopter.h"
#include "GameWorld.h"
#include "Bomb.h"
#include "Paratrooper.h"

#include <math.h>
#include <algorithm>

#include "HealthComponent.h"
#include "MovementComponent.h"
#include "ParachuteComponent.h"

EnemySpawner::EnemySpawner()
{
}

EnemySpawner::~EnemySpawner()
{
	myEntities.clear();
}

void EnemySpawner::Init(GameWorld& aGameWorld, UIManager& aUIManager)
{
	myGameWorld = &aGameWorld;
	myUIManager = &aUIManager;
}

void EnemySpawner::Update(float aTimeDelta)
{
	for (auto& entity : myEntities)
	{
		entity->Update(aTimeDelta);
	}

	for (auto& pendingEntity : myPendingEntities)
	{
		myEntities.push_back(std::move(pendingEntity));
	}

	myPendingEntities.clear();

	myTimer += aTimeDelta;
	myTimeBeforeJets -= aTimeDelta;

	if (globalInputHandler.IsKeyPressed(KEY_SHIFT))
	{
		SpawnHelicopters();
	}

	if (CanSpawnHelicopter())
	{
		SpawnHelicopters();
	}

	if (myActivateSmartBomb)
	{
		for (auto& enemy : myEntities)
		{
			if (auto enemyHealth = enemy->GetComponent<HealthComponent>())
			{
				enemyHealth->OnTakeDamage(1);
			}
		}
		myActivateSmartBomb = false;
	}

	std::erase_if(myEntities, [](const std::unique_ptr<Entity>& aEntity)
	{
		auto health = aEntity->GetComponent<HealthComponent>();
		return health && health->GetHealthState() == HealthState::Destroy;
	});


	if (myShouldRestart)
	{
		Restart();
	}
}

void EnemySpawner::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	for (const auto& entity : myEntities)
	{
		aSpriteDrawer.Draw(entity->GetSpriteData(), entity->GetSpriteInstance());
		//entity->Render(aSpriteDrawer);
	}
}

void EnemySpawner::IncrementTroopReached(Paratrooper& aTrooper)
{
	if (aTrooper.GetLeftSide())
	{
		myTroopsLeft++;
	}
	else
	{
		myTroopsRight++;
	}

	aTrooper.SetState(State::Scored);
	aTrooper.IncrementDistanceOffset(15.0);
}

bool EnemySpawner::HasTroopsFinished() const
{
	if (myTroopsRight >= 4 || myTroopsLeft >= 4)
	{
		return true;
	}
	return false;
}

bool EnemySpawner::CanSpawnHelicopter()
{
	if (myTimer <= myTimeToSpawn)
	{
		return false;
	}

	++myHelicoptersSpawned;

	myTimeToSpawn -= 0.15f / myHelicoptersSpawned;
	myTimeToSpawn = (std::max)(myTimeToSpawn, 0.2f);

	return true;
}

void EnemySpawner::SpawnHelicopters()
{
	auto helicopter = std::make_unique<Entity>();
	auto helicopterMovement = helicopter->AddComponent<MovementComponent>();
	auto heliHealthComp = helicopter->AddComponent<HealthComponent>();
	auto helicopterComp = helicopter->AddComponent<Helicopter>();

	helicopterComp->SetOnSpawnTrooper([this](const Tga::Vector2f& aPosition)
	{
		auto trooper = std::make_unique<Entity>();
		trooper->AddComponent<MovementComponent>();
		auto trooperhealthComp = trooper->AddComponent<HealthComponent>();
		auto trooperComp = trooper->AddComponent<Paratrooper>();

		trooper->SetPosition(aPosition);

		if (trooperComp->GetLeftSide())
		{
			trooperComp->IncrementDistanceOffset(myTroopsLeft * 15.0f);
		}
		if (!trooperComp->GetLeftSide())
		{
			trooperComp->IncrementDistanceOffset(myTroopsRight * 15.0f);
		}

		trooperComp->SetOnReachedPlayer([this](Paratrooper* trooper)
		{
			IncrementTroopReached(*trooper);
			if (HasTroopsFinished())
			{
				myShouldRestart = true;
			}
		});

		trooperComp->SetOnOpenParachute([this](Entity* aEntity)
		{
			auto parachute = std::make_unique<Entity>();
			auto movementComp = parachute->AddComponent<MovementComponent>();
			auto parachuteHealthComp = parachute->AddComponent<HealthComponent>();
			auto parachuteComp = parachute->AddComponent<ParachuteComponent>();

			parachuteComp->SetParachuteTrooper(aEntity);
			parachute->SetPosition(aEntity->GetPosition() + Tga::Vector2f{0.0f, 150.0f});
			movementComp->SetMovement(aEntity->GetComponent<MovementComponent>()->GetMovement());

			if (auto trooper = aEntity->GetComponent<Paratrooper>())
			{
				trooper->SetParachute(parachute.get());
			}

			myPendingEntities.push_back(std::move(parachute));

			//UNREFERENCED_PARAMETER();
		});

		trooperhealthComp->SetOnDeath([this](Entity* aEntity)
		{
			if (auto trooper = aEntity->GetComponent<Paratrooper>())
			{
				trooper->SetParachuteDestroyed();
			}

			Tga::Vector2f spawnPosition = aEntity->GetPosition();
			myGameWorld->SpawnParticle(ParticlePreset::CircleSpread, spawnPosition);
		});

		myPendingEntities.push_back(std::move(trooper));
	});

	heliHealthComp->SetOnDeath([&](Entity* aEntity)
	{
		Tga::Vector2f spawnPosition = aEntity->GetPosition();
		myGameWorld->SpawnParticle(ParticlePreset::CircleSpread, spawnPosition);
	});

	myPendingEntities.push_back(std::move(helicopter));

	myTimer = 0.0f;

	//if (myHelicoptersSpawned % 2 == 0 && myTimeBeforeJets <= 0)
	//{
	//	SpawnJet();
	//}
}

void EnemySpawner::SpawnJet()
{
	auto jetEntity = std::make_unique<Entity>();
	jetEntity->AddComponent<MovementComponent>();
	auto jetHealthComp = jetEntity->AddComponent<HealthComponent>();
	auto jetComponent = jetEntity->AddComponent<Jet>();

	jetHealthComp->SetOnDeath([this](const Entity* aEntity)
	{
		Tga::Vector2f spawnPosition = aEntity->GetPosition();
		myGameWorld->SpawnParticle(ParticlePreset::CircleSpread, spawnPosition);
	});

	jetComponent->SetOnDropBomb([this](const Tga::Vector2f aPosition)
	{
		auto bombEntity = std::make_unique<Entity>();
		auto bombMovement = bombEntity->AddComponent<MovementComponent>();
		bombEntity->AddComponent<HealthComponent>();
		auto bombComp = bombEntity->AddComponent<Bomb>();
		bombEntity->SetPosition(aPosition);

		bombComp->SetOnExplode([this]()
		{
			myShouldRestart = true;
		});

		myPendingEntities.push_back(std::move(bombEntity));
	});

	myPendingEntities.push_back(std::move(jetEntity));
}

void EnemySpawner::ActivateSmartBomb()
{
	myActivateSmartBomb = true;
}

void EnemySpawner::ClearAllEnemies()
{
	myPendingEntities.clear();
	myEntities.clear();
}

void EnemySpawner::Restart()
{
	ClearAllEnemies();
	myShouldRestart = false;

	myTimer = 0;
	myTimeToSpawn = 4.0f;
	myHelicoptersSpawned = 0;
	myTimeBeforeJets = 10.0f;

	myTroopsLeft = 0;
	myTroopsRight = 0;

	myUIManager->GameOver();
}

int EnemySpawner::GetEnemyPointsCount() const
{
	int heliCount = 0;
	int trooperCount = 0;
	int jetCount = 0;

	for (const auto& entity : myEntities)
	{
		if (entity->GetComponent<Helicopter>())
		{
			heliCount++;
		}
		if (entity->GetComponent<Paratrooper>())
		{
			trooperCount++;
		}
		if (entity->GetComponent<Jet>())
		{
			jetCount++;
		}
	}
	return heliCount * 10 + trooperCount * 5 + jetCount * 10;
}
