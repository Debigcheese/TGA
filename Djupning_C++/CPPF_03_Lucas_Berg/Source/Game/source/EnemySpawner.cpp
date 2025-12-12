#include "EnemySpawner.h"

#include "Helicopter.h"

EnemySpawner::EnemySpawner()
{
}

EnemySpawner::~EnemySpawner()
{
	myEnemies.clear();
}

void EnemySpawner::Init(UIManager& aUIManager)
{
	myUIManager = &aUIManager;
}

void EnemySpawner::Update(float aTimeDelta)
{
	myPendingEnemies.clear();
	myPendingParticleSystems.clear();

	for (auto& enemy : myEnemies)
	{
		enemy->Update(aTimeDelta);
	}

	for (auto& pendingEnemy : myPendingEnemies)
	{
		myEnemies.push_back(std::move(pendingEnemy));
	}

	for (auto& particleSystem : myParticleSystems)
	{
		particleSystem->Update(aTimeDelta);
	}

	for (auto& pendingParticle : myPendingParticleSystems)
	{
		myParticleSystems.push_back(std::move(pendingParticle));
	}

	myTimer += aTimeDelta;
	myTimeBeforeJets -= aTimeDelta;

	if (CanSpawnHelicopter())
	{
		SpawnHelicopters();
	}

	std::erase_if(myEnemies, [](const std::unique_ptr<Enemy>& aEnemy)
	{
		return aEnemy->GetLifeState() == LifeState::Destroy;
	});

	std::erase_if(myParticleSystems, [](const std::unique_ptr<ParticleSystem>& aParticleSystem)
	{
		return !aParticleSystem->GetIsActive();
	});

	if (myShouldRestart)
	{
		Restart();
	}
}

void EnemySpawner::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	for (const auto& enemy : myEnemies)
	{
		enemy->Render(aSpriteDrawer);
	}

	for (const auto& particleSystem : myParticleSystems)
	{
		particleSystem->Render(aSpriteDrawer);
	}
}

void EnemySpawner::IncrementTroopReached(Paratrooper& aTrooper)
{
	if (aTrooper.GetSide() == Side::Left)
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
	myHelicoptersSpawned++;

	if (myHelicoptersSpawned <= 0)
	{
		return false;
	}

	myTimeToSpawn -= 0.15f / myHelicoptersSpawned;

	myTimeToSpawn = std::max(myTimeToSpawn, 0.2f);

	return true;
}

void EnemySpawner::SpawnHelicopters()
{
	auto helicopter = std::make_unique<Helicopter>();

	helicopter->SetOnSpawnTrooper([this](const Tga::Vector2f& aPosition)
	{
		auto trooper = std::make_unique<Paratrooper>();
		trooper->SetPosition(aPosition);

		if (trooper->GetSide() == Side::Left)
		{
			trooper->IncrementDistanceOffset(myTroopsLeft * 15.0f);
		}
		if (trooper->GetSide() == Side::Right)
		{
			trooper->IncrementDistanceOffset(myTroopsRight * 15.0f);
		}

		trooper->SetOnReachedPlayer([this](Paratrooper* trooper)
		{
			IncrementTroopReached(*trooper);
			if (HasTroopsFinished())
			{
				myShouldRestart = true;
			}
		});

		myPendingEnemies.push_back(std::move(trooper));
	});

	helicopter->SetOnDeath([this](const Enemy* aEnemy)
	{
		auto particleSystem = std::make_unique<ParticleSystem>();
		EmitterSetting setting;
		setting.count = 100;
		particleSystem->Init(setting);

		particleSystem->SetPosition(aEnemy->GetPosition());
		particleSystem->Play();

		myPendingParticleSystems.push_back(std::move(particleSystem));
	});

	myEnemies.push_back(std::move(helicopter));
	myTimer = 0.0f;

	if (myHelicoptersSpawned % 3 == 0 && myTimeBeforeJets <= 0)
	{
		SpawnJet();
	}
}

void EnemySpawner::SpawnJet()
{
	auto jet = std::make_unique<Jet>();

	jet->SetOnDropBomb([this](const Tga::Vector2f aPosition)
	{
		auto bomb = std::make_unique<Bomb>();
		bomb->SetPosition(aPosition);

		bomb->SetOnExplode([this]()
		{
			myShouldRestart = true;
		});

		myPendingEnemies.push_back(std::move(bomb));
	});

	myEnemies.push_back(std::move(jet));
}

void EnemySpawner::ClearAllEnemies()
{
	myEnemies.clear();
	myPendingEnemies.clear();
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

	for (const auto& enemy : myEnemies)
	{
		switch (enemy->GetType())
		{
			case EnemyType::Helicopter:
				{
					heliCount++;
					break;
				}
			case EnemyType::Paratrooper:
				{
					trooperCount++;
					break;
				}
			case EnemyType::Jet:
				{
					jetCount++;
					break;
				}
			default:
				{
					break;
				}
		}
	}
	return heliCount * 10 + trooperCount * 5 + jetCount * 10;
}
