#pragma once
#include "tge/Engine.h"

class GameState
{
public:
	GameState();

	void Init(Tga::Engine& aEngine);
	void Reset() { myPlayerScore = 0; }

	void SetStartGame(bool aStartGame) { myGameStarted = aStartGame; }
	bool HasGameStarted() const { return myGameStarted; }

	void SetPauseGame(bool aPauseGame) { myGamePaused = aPauseGame; }
	bool IsGamePaused() const { return myGamePaused; }

	int GetScore() const { return myPlayerScore; }
	int UpdateScore() { return myPlayerScore++; }

private:
	Tga::Vector2f myScreenResolution;

	int myPlayerScore;
	bool myGameStarted;
	bool myGamePaused;
};
