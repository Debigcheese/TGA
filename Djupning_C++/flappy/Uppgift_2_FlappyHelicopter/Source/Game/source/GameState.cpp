#include "GameState.h"

GameState::GameState() : myPlayerScore(0), myEnemyScore(0)
{
}

void GameState::Init(Tga::Engine& aEngine)
{
	//Get resolution
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};
	myGameStarted = false;
}

void GameState::Reset()
{
	myEnemyScore = 0;
	myPlayerScore = 0;
}

int GameState::GetScore(Actor aActor) const
{
	if (aActor == Actor::Player)
	{
		return myPlayerScore;
	}
	return myEnemyScore;
}

int GameState::UpdateScore(Actor aActor)
{
	if (aActor == Actor::Player)
	{
		return myPlayerScore++;
	}
	return myEnemyScore++;
}


bool GameState::GameOver() const
{
	int playerScore = GetScore(Actor::Player);
	int enemyScore = GetScore(Actor::Enemy);

	if (playerScore >= 3 || enemyScore >= 3)
	{
		return true;
	}
	return false;
}

Actor GameState::GetWinner() const
{
	int playerScore = GetScore(Actor::Player);
	int enemyScore = GetScore(Actor::Enemy);

	if (playerScore >= 3)
	{
		return Actor::Player;
	}
	if (enemyScore >= 3)
	{
		return Actor::Enemy;
	}

	return Actor::None;
}
