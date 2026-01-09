#pragma once
#include "UIManager.h"
#include "ParticleSystem.h"
#include "Entity.h"

class GameWorld;
class Paratrooper;

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();

	void Init(GameWorld& aGameWorld, UIManager& aUIManager);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);

	void IncrementTroopReached(Paratrooper& aTrooper);
	bool HasTroopsFinished() const;

	bool CanSpawnHelicopter();
	void SpawnHelicopters();
	void SpawnJet();

	void ActivateSmartBomb();
	void ClearAllEnemies();
	void Restart();

	int GetEnemyPointsCount() const;

	std::vector<std::unique_ptr<Entity>>& GetEntities() { return myEntities; }

private:
	GameWorld* myGameWorld;
	UIManager* myUIManager;

	int myTroopsLeft = 0;
	int myTroopsRight = 0;

	int myHelicoptersSpawned = 0;
	float myTimeToSpawn = 3.25f;
	float myTimer = 0.0f;
	float myTimeBeforeJets = 0.0f;

	bool myShouldRestart = false;
	bool myActivateSmartBomb = false;

	std::vector<std::unique_ptr<Entity>> myEntities;
	std::vector<std::unique_ptr<Entity>> myPendingEntities;
};
