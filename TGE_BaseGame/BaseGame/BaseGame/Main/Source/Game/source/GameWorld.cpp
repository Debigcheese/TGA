#include "GameWorld.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/engine.h>
#include <tge/settings/settings.h>

#include "HealthComponent.h"
#include "CommonUtilities/Random.h"

using namespace Tga;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
	//for (auto* fireball : myFireballs)
	//{
	//	delete fireball;
	//}
	//myFireballs.clear();
}

void GameWorld::Init()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	globalRNG.Seed(123456);

	myInput = &globalInputHandler;
	myUIManager.Init();
	myPlayer.Init(myInput, myUIManager);
	myEnemySpawner.Init(*this, myUIManager);

	auto ground = std::make_unique<Entity>();
	ground->SetTexture("Sprites/ground.png");
	ground->SetPivot({0.5f, 0.5f});
	ground->SetPosition({myScreenResolution.x / 2, 40.0f});
	ground->SetScale({3.0f, 1.0f});

	auto tower = std::make_unique<Entity>();
	tower->SetTexture("Sprites/CannonTower.png");
	tower->SetPivot({0.5f, 0.5f});
	tower->SetPosition({myScreenResolution.x / 2, 80.0f});
	tower->SetScale({1.0f, 1.0f});

	myEntities.push_back(std::move(ground));
	myEntities.push_back(std::move(tower));

	// Start the logic thread and calls Update() repeatedly
	//myThreadingManager.StartLogicThread([this](float dt)
	//{
	//	this->Update(dt);
	//	myInput->UpdateInput();
	//});

	myPlayer.SetOnInputPressCallback([this](const char input)
	{
		if (input == 'S')
		{
			if (myPlayer.GetSmartBombs() <= 0)
			{
				return;
			}

			myPlayer.SetSmartBombs(myPlayer.GetSmartBombs() - 1);

			myUIManager.GainScore(myEnemySpawner.GetEnemyPointsCount());
			myEnemySpawner.ActivateSmartBomb();
			myUIManager.SetSmartBombText(myPlayer.GetSmartBombs());
		}
	});
}

void GameWorld::Update(float aTimeDelta)
{
	myUIManager.SetOnStartGameCallback([this]()
	{
		myStartGame = true;
	});

	myUIManager.Update(aTimeDelta, myInput);

	myPlayer.Update(aTimeDelta);

	UpdateParticles(aTimeDelta);

	if (myUIManager.GetGameState() == GameState::InGame)
	{
		myEnemySpawner.Update(aTimeDelta);
	}
	if (myUIManager.GetGameState() == GameState::Restart)
	{
		myEnemySpawner.Restart();
		myUIManager.GameOver();
		myPlayer.SetSmartBombs(3);
	}

	HandleCollision();
	myInput->UpdateInput();
}

void GameWorld::UpdateParticles(float aTimeDelta)
{
	for (auto& pendingParticleSystem : myPendingParticleSystems)
	{
		myParticleSystems.push_back(std::move(pendingParticleSystem));
	}

	myPendingParticleSystems.clear();

	for (auto& particleSystem : myParticleSystems)
	{
		particleSystem->Update(aTimeDelta);
	}

	std::erase_if(myParticleSystems, [](const std::unique_ptr<ParticleSystem>& aParticleSystem)
	{
		return !aParticleSystem->GetIsActive();
	});
}

void GameWorld::Render()
{
	auto& spriteDrawer = Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();
	myUIManager.Render(spriteDrawer);
	myPlayer.Render(spriteDrawer);
	myEnemySpawner.Render(spriteDrawer);

	spriteDrawer.Draw(myEntities[0]->GetSpriteData(), myEntities[0]->GetSpriteInstance());
	spriteDrawer.Draw(myEntities[1]->GetSpriteData(), myEntities[1]->GetSpriteInstance());

	for (const auto& particleSystem : myParticleSystems)
	{
		particleSystem->Render(spriteDrawer);
	}

	//myThreadingManager.SyncAndSwap([this]()
	//{
	//	myRenderCommand.Swap();
	//});

	//myRenderCommand.Execute();

	//myThreadingManager.SignalRenderDone();
}

void GameWorld::HandleCollision()
{
	auto& entities = myEnemySpawner.GetEntities();

	for (auto& particleSystem : myParticleSystems)
	{
		if (!particleSystem->GetIsActive())
		{
			return;
		}
		for (auto& particle : particleSystem->GetParticles())
		{
			for (auto& staticEntity : myEntities)
			{
				AABB aabb_1({particle->GetPosition(), particle->GetSize()});
				AABB aabb_2({staticEntity->GetPosition(), staticEntity->GetSize()});

				if (CheckCollision(aabb_1, aabb_2))
				{
					particle->OnCollided();
					staticEntity->OnCollided();
				}
			}
		}
	}

	for (auto& entity : entities)
	{
		for (auto& bulletEntity : myPlayer.GetBullets())
		{
			AABB aabb_1({entity->GetPosition(), entity->GetSize()});
			AABB aabb_2({bulletEntity->GetPosition(), bulletEntity->GetSize()});

			if (!CheckCollision(aabb_1, aabb_2))
			{
				continue;
			}

			if (auto healthComp = entity->GetComponent<HealthComponent>())
			{
				if (healthComp->GetHealthState() != HealthState::Alive)
				{
					continue;
				}
				healthComp->OnTakeDamage(1);
			}

			if (entity->GetComponent<Paratrooper>())
			{
				myUIManager.GainScore(5);
			}
			else
			{
				myUIManager.GainScore(10);
			}
		}
	}
}

bool GameWorld::CheckCollision(AABB aAABB, AABB aBBAA) const
{
	const Tga::Vector2f sizeHalfA = {std::abs(aAABB.aSize.x / 2), std::abs(aAABB.aSize.x / 2)};
	const Tga::Vector2f sizeHalfB = {std::abs(aBBAA.aSize.x / 2), std::abs(aBBAA.aSize.y / 2)};

	const float dx = std::fabs(aAABB.aPosition.x - aBBAA.aPosition.x);
	const float dy = std::fabs(aAABB.aPosition.y - aBBAA.aPosition.y);

	return (dx <= (sizeHalfA.x + sizeHalfB.x)) && (dy <= (sizeHalfA.y + sizeHalfB.y));
}

void GameWorld::SpawnParticle(ParticlePreset aPreset, const Tga::Vector2f& aPosition)
{
	auto particleSystem = std::make_unique<ParticleSystem>();
	particleSystem->Init(aPreset);
	particleSystem->SetPosition(aPosition);
	particleSystem->Play();

	myPendingParticleSystems.push_back(std::move(particleSystem));
}
