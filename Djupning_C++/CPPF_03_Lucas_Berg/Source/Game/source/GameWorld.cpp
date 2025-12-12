#include "GameWorld.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/engine.h>
#include <tge/settings/settings.h>
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

	myEnemySpawner.Init(myUIManager);

	myGroundData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/ground.png");
	myGroundInstance.myPivot = {0.5f, 0.5f};
	myGroundInstance.myPosition = {myScreenResolution.x / 2, 40.0f};
	myGroundInstance.mySize = myGroundData.myTexture->CalculateTextureSize();
	myGroundInstance.mySizeMultiplier = 3.0f;

	myTowerData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/CannonTower.png");
	myTowerInstance.myPivot = {0.5f, 0.5f};
	myTowerInstance.myPosition = {myScreenResolution.x / 2, 80.0f};
	myTowerInstance.mySize = myTowerData.myTexture->CalculateTextureSize();

	// Start the logic thread and calls Update() repeatedly
	myThreadingManager.StartLogicThread([this](float dt)
	{
		this->Update(dt);
		myInput->UpdateInput();
	});

	myPlayer.SetOnInputPressCallback([this](const char input)
	{
		if (input == 'S')
		{
			if (myPlayer.GetSmartBombs() <= 0) { return; }

			myPlayer.SetSmartBombs(myPlayer.GetSmartBombs() - 1);

			myUIManager.GainScore(myEnemySpawner.GetEnemyPointsCount());
			myEnemySpawner.ClearAllEnemies();
			myUIManager.SetSmartBombText(myPlayer.GetSmartBombs());
		}

		if (input == KEY_LMB)
		{
		}
		if (input == KEY_SPACE)
		{
			myStartGame = true;
			myUIManager.StartGame();
		}
		if (input == 'P')
		{
			myUIManager.PauseGame();
		}
		if (input == 'I')
		{
			myUIManager.ShowInstructions();
		}
		if (input == KEY_ESCAPE)
		{
			Tga::Engine& engine = *Tga::Engine::GetInstance();
			engine.Shutdown(); // dont know any better way 
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
}

void GameWorld::Render()
{
	auto& spriteDrawer = Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();
	myUIManager.Render(spriteDrawer);
	myPlayer.Render(spriteDrawer);
	myEnemySpawner.Render(spriteDrawer);

	spriteDrawer.Draw(myGroundData, myGroundInstance);
	spriteDrawer.Draw(myTowerData, myTowerInstance);

	myThreadingManager.SyncAndSwap([this]()
	{
		myRenderCommand.Swap();
	});

	myRenderCommand.Execute();

	myThreadingManager.SignalRenderDone();
}

void GameWorld::HandleCollision()
{
	auto& enemies = myEnemySpawner.GetEnemies();

	for (auto& enemy : enemies)
	{
		for (auto& bullet : myPlayer.GetBullets())
		{
			AABB aabb_1({enemy->GetPosition(), enemy->GetSize()});
			AABB aabb_2({bullet.GetPosition(), bullet.GetSize()});

			if (enemy->GetType() == EnemyType::Paratrooper)
			{
				auto* trooper = static_cast<Paratrooper*>(enemy.get());
				AABB aabb_3({trooper->GetParachutePosition(), trooper->GetParachuteSize()});
				AABB aabb_4({bullet.GetPosition(), bullet.GetSize()});

				if (CheckCollision(aabb_3, aabb_4))
				{
					trooper->SetState(State::Falling);
				}
			}

			if (!CheckCollision(aabb_1, aabb_2))
			{
				continue;
			}

			if (enemy->GetLifeState() != LifeState::Alive)
			{
				continue;
			}

			enemy->OnDeath();

			if (enemy->GetType() == EnemyType::Paratrooper)
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
