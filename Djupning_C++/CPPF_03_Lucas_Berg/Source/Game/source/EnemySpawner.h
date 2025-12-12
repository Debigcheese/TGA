#pragma once
#include "Enemy.h"
#include "Helicopter.h"
#include "Jet.h"
#include "Paratrooper.h"
#include "UIManager.h"
#include "Bomb.h"
#include "ParticleSystem.h"

class Bomb;

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();

	void Init(UIManager& aUIManager);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);

	void IncrementTroopReached(Paratrooper& aTrooper);
	bool HasTroopsFinished() const;

	bool CanSpawnHelicopter();
	void SpawnHelicopters();
	void SpawnJet();

	void ClearAllEnemies();
	void Restart();

	int GetEnemyPointsCount() const;

	const std::vector<std::unique_ptr<Enemy>>& GetEnemies() const { return myEnemies; }

private:
	UIManager* myUIManager;

	int myTroopsLeft = 0;
	int myTroopsRight = 0;

	int myHelicoptersSpawned = 0;
	float myTimeToSpawn = 3.25f;
	float myTimer = 0.0f;
	float myTimeBeforeJets = 10.0f;
	bool myShouldRestart = false;

	std::vector<std::unique_ptr<Enemy>> myEnemies;
	std::vector<std::unique_ptr<Enemy>> myPendingEnemies;

	std::vector<std::unique_ptr<ParticleSystem>> myParticleSystems;
	std::vector<std::unique_ptr<ParticleSystem>> myPendingParticleSystems;
};
