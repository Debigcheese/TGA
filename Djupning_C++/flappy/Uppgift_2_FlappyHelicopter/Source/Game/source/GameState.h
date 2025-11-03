#pragma once
#include "Config.h"
#include "tge/Engine.h"

class GameState
{
public:
	GameState();

	void Init(Tga::Engine& aEngine);
	void Reset();

	void SetStartGame(bool aStartGame) { myGameStarted = aStartGame; }
	bool HasGameStarted() const { return myGameStarted; }

	int GetScore(Actor aActor) const;
	int UpdateScore(Actor aActor);

	bool GameOver() const;
	Actor GetWinner() const;

private:
	Tga::Vector2f myScreenResolution;

	bool myGameStarted;

	int myPlayerScore;
	int myEnemyScore;
};
