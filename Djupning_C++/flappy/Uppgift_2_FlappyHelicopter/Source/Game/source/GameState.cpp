#include "GameState.h"

GameState::GameState() : myPlayerScore(0)
{
}

void GameState::Init(Tga::Engine& aEngine)
{
	//Get resolution
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};
	myGameStarted = false;
}
