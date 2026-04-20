// Main.cpp : Defines the entry point for the application.

#include "framework.h"
#include "Main.h"
#include "Engine.h"
#include "GameWorld.h"

int APIENTRY wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPWSTR    lpCmdLine,
	_In_     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Start engine 
	EngineConfiguration engineConfig;
	engineConfig.hInstance = hInstance;
	engineConfig.nCmdShow = nCmdShow;
	engineConfig.windowWidth = 1280;
	engineConfig.windowHeight = 720;
	engineConfig.windowTitle = L"TGP Graphics";

	if (!Engine::Start(engineConfig))
		return FALSE;

	// Initialize game world
	Engine& engine = *Engine::GetInstance();

	GameWorld gameWorld;
	if (!gameWorld.Init())
	{
		Engine::Shutdown();
		return FALSE;
	}

	// Main loop 
	while (engine.BeginFrame())
	{
		gameWorld.Update(engine.GetDeltaTime());
		gameWorld.Render();
		engine.EndFrame();
	}

	Engine::Shutdown();
	return 0;
}