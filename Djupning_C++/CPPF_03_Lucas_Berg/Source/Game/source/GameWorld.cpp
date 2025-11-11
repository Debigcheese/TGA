#include "GameWorld.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>
#include <tge/engine.h>

#include <tge/settings/settings.h>

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
	myHelicopter->Init(engine, myGameState);

	myPlayer->Possess(myHelicopter);

	myTerrain = new Terrain;
	myTerrain->Init(engine);
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
		myHelicopter->Update(aTimeDelta);
		return;
	}

	myHelicopter->Update(aTimeDelta);
	myPlayer->Update(aTimeDelta);
	myHud->Update(aTimeDelta, *myGameState);

	myTerrain->Update(aTimeDelta);

	HandleCollision();
	HandleScore();

	UNREFERENCED_PARAMETER(aTimeDelta);
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
	myHud->ShowFinish(false);
	myHud->ShowRestart(false);
	myHud->ShowIntro(false);

	myHelicopter->Reset();

	myGameState->Reset();
	myGameState->SetStartGame(true);
	myTerrain->ResetTerrain();
}

void GameWorld::HandleCollision()
{
	auto& pieces = myTerrain->GetPieces();

	for (auto& piece : pieces)
	{
		if (myHelicopter->CheckCollision(piece.GetPosition(), piece.GetSize()))
		{
			HandleGameOver();
		}
	}
}

void GameWorld::HandleScore() const
{
	Tga::Vector2f playerPos = myHelicopter->GetPosition();
	std::vector<TerrainPiece>& pieces = myTerrain->GetPieces();

	for (auto& piece : pieces)
	{
		if (playerPos.x >= piece.GetPosition().x && piece.GetId() % 2 == 0 && !piece.GetHasScored())
		{
			piece.SetHasScored();
			myGameState->UpdateScore();
		}
	}
}

void GameWorld::HandlePause() const
{
	if (!myGameState->IsGamePaused())
	{
		//myHelicopter->SetActive(false);
		myTerrain->StopTerrainMovement();
		return;
	}
	else
	{
		//myHelicopter->SetActive(true);
		myTerrain->ResumeTerrainMovement();
	}
}

void GameWorld::HandleGameOver() const
{
	myHelicopter->OnDeath();
	myHud->ShowRestart(true);
	myTerrain->StopTerrainMovement();
	myGameState->SetStartGame(false);
	//myHud->ShowFinish(true);
}

void GameWorld::Render() const
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());

	myPlayer->Render(spriteDrawer);
	myHelicopter->Render(spriteDrawer);
	myPlayer->GetHelicopter()->Render(spriteDrawer);
	myTerrain->Render(spriteDrawer);

	myHud->Render(spriteDrawer);

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
