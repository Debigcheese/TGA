#include "GameWorld.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>
#include <tge/engine.h>

#include <tge/settings/settings.h>
#include <tge/sprite/sprite.h>

#include "Enemy.h"
#include "CommonUtilities/Random.h"

using namespace Tga;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
	delete myGameState;
	delete myHud;
	delete myPlayer;
	delete myHelicopter;
}

//Load all graphic, sounds, etc
void GameWorld::Init()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	myScreenResolution = {(float)intResolution.x, (float)intResolution.y};
	{
		//mySharedData.myTexture = engine.GetTextureManager().GetTexture("Sprites/tge_logo_w.dds");

		myTGELogoInstance.myPivot = {0.5f, 0.5f};
		myTGELogoInstance.myPosition = Tga::Vector2f{0.5f, 0.5f} * myScreenResolution;
		myTGELogoInstance.mySize = Tga::Vector2f{0.75f, 0.75f} * myScreenResolution.y;
		myTGELogoInstance.myColor = Tga::Color(1, 1, 1, 1);
	}

	Tga::LoadSettings(TGE_PROJECT_SETTINGS_FILE);

	globalRNG.Seed(123456u);

	myBounds.minX = 35.0f;
	myBounds.maxX = myScreenResolution.x - 35.0f;

	myGameState = new GameState();
	myGameState->Init(engine);

	myHud = new HUD;
	myHud->Init(engine);

	myPlayer = new Player();
	myPlayer->Init(engine);

	myHelicopter = new Helicopter();
	myHelicopter->Init(engine);

	myPlayer->Possess(myHelicopter);
}

void GameWorld::Update(float aTimeDelta)
{
	CheckInit();

	auto input = myPlayer->GetInput();

	if ((input->IsKeyPressed(KEY_ENTER) ||
			input->IsKeyReleased(KEY_ENTER)) &&
		!myGameState->HasGameStarted())
	{
		StartGame();
	}
	if (!myGameState->HasGameStarted())
	{
		return;
	}

	myPlayer->Update(aTimeDelta);
	myHud->Update(aTimeDelta, *myGameState);
	myHelicopter->Update(aTimeDelta);

	HandleCollision();
	HandleScore();

	GenerateTerrain();

	if (myGameState->GameOver())
	{
		HandleGameOver();
	}

	UNREFERENCED_PARAMETER(aTimeDelta);
}

void GameWorld::GenerateTerrain(float aTimeDelta)
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();

	Terrain* t1 = new Terrain;
	t1->Init(engine);

	Terrain terrain1 = new Terrain();
}

void GameWorld::CheckInit()
{
	if (!myPlayer)
	{
		std::cout << "\nNo player in game world!" << std::endl;
	}

	if (!myHelicopter)
	{
		std::cout << "\nNo helicopter in game world!" << std::endl;
	}

	if (!myGameState)
	{
		std::cout << "GameState does not exist";
	}
}

void GameWorld::StartGame()
{
	myGameState->SetStartGame(true);
	//myGameState->Reset();

	myHud->ShowFinish(false);
	myHud->ShowRestart(false);
	myHud->ShowIntro(false);

	myHelicopter->SetVisibility(true);
	//myHelicopter->Reset();
	myPlayer->GetHelicopter()->SetVisibility(true);
	myGameState->SetStartGame(true);
}

void GameWorld::HandleCollision() const
{
	//auto playerPos = myPlayer->GetHelicopter()->GetPosition();
	//auto playerSize = myPlayer->GetHelicopter()->GetSize();

	//auto enemyPos = GetHelicopter->GetHelicopter()->GetPosition();
	//auto enemySize = GetHelicopter->GetHelicopter()->GetSize();

	//if (myBall->CheckCollision(playerPos, playerSize))
	//{
	//	myBall->ResolveCollision(enemyPos, enemySize);
	//	myBall->SwitchDirection();
	//	myBall->Bounce();
	//}

	//if (myBall->CheckCollision(enemyPos, enemySize))
	//{
	//	myBall->ResolveCollision(enemyPos, enemySize);
	//	myBall->SwitchDirection();
	//	myBall->Bounce();
	//}
}

void GameWorld::HandleScore() const
{
	//Tga::Vector2f ballPos = myBall->GetPosition();

	//if (ballPos.x > myBounds.maxX)
	//{
	//	myGameState->UpdateScore(Actor::Player);
	//	myBall->Reset();
	//	myHud->LerpTextSize(4.0f, 0.125f);
	//}
	//else if (ballPos.x < myBounds.minX)
	//{
	//	myGameState->UpdateScore(Actor::Enemy);
	//	myBall->Reset();
	//	myHud->LerpTextSize(4.0f, 0.125f);
	//}
}

void GameWorld::HandleGameOver()
{
	//Actor winner = myGameState->GetWinner();

	//if (winner == Actor::Player)
	//{
	//	myHud->SetGameOverStr("You Win!");
	//}
	//else if (winner == Actor::Enemy)
	//{
	//	myHud->SetGameOverStr("You Lose!");
	//}
	//myBall->Disable();

	//myHud->ShowRestart(true);
	//myHud->ShowFinish(true);

	//myGameStarted = false;
}

void GameWorld::Render() const
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());

	myPlayer->Render(spriteDrawer);
	myHelicopter->Render(spriteDrawer);
	myPlayer->GetHelicopter()->Render(spriteDrawer);

	myHud->Render();

	// Debug draw pivot
#ifndef _RETAIL
	//{
	//	Tga::DebugDrawer& dbg = engine.GetDebugDrawer();
	//	Tga::Color c1 = myTGELogoInstance.myColor;
	//	dbg.DrawCircle(myTGELogoInstance.myPosition, 5.f,
	//	               (c1.myR + c1.myG + c1.myB) / 3 > 0.3f ? Tga::Color(0, 0, 0, 1) : Tga::Color(1, 1, 1, 1));
	//}
#endif
}
