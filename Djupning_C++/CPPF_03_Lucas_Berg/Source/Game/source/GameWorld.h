#pragma once
#include "GameState.h"
#include "Helicopter.h"
#include "HUD.h"
#include "Player.h"
#include "Terrain.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Init();
	void Update(float aTimeDelta);
	void Render() const;

	void StartGame();

	void HandleCollision();
	void HandleGameOver() const;
	void HandleScore() const;

private:
	Tga::Vector2f myScreenResolution;

	Bounds myBounds;
	GameState* myGameState;
	HUD* myHud;

	Player* myPlayer;
	Helicopter* myHelicopter;
	Terrain* myTerrain;
};
