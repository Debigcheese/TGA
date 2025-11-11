#include "GameState.h"

GameState::GameState() : myScreenResolution{1920, 1080}, myPlayerScore(0), myGameStarted(false)
{
}

void GameState::Init(Tga::Engine& aEngine)
{
	//Get resolution
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};
	myGameStarted = false;
	myGamePaused = false;
}
