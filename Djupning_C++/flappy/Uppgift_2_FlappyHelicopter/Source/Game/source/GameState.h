#pragma once
#include "Config.h"
#include "tge/Engine.h"

class GameState
{
public:
	GameState();

	void Init(Tga::Engine& aEngine);
	void Reset() { myPlayerScore = 0; }

	void SetStartGame(bool aStartGame) { myGameStarted = aStartGame; }
	bool HasGameStarted() const { return myGameStarted; }

	int GetScore() const { return myPlayerScore; }
	int UpdateScore() { return myPlayerScore++; }

private:
	Tga::Vector2f myScreenResolution;

	bool myGameStarted;
	int myPlayerScore;
};
