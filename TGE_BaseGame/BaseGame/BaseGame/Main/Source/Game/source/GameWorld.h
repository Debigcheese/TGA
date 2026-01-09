#pragma once
#include "EnemySpawner.h"
#include "Player.h"
#include "tge/math/Vector2.h"
#include "CommonUtilities/InputHandler.h"
#include "RenderCommand.h"
#include "ThreadingManager.h"
#include "UIManager.h"
#include "Entity.h"

using Input = CommonUtilities::InputHandler;

struct AABB
{
	Tga::Vector2f aPosition;
	Tga::Vector2f aSize;
};

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Init();
	void Update(float aTimeDelta);
	void UpdateParticles(float aTimeDelta);
	void Render();

	void HandleCollision();
	bool CheckCollision(AABB aAABB, AABB aBBAA) const;
	void SpawnParticle(ParticlePreset aPreset, const Tga::Vector2f& aPosition);

	Input* GetInput() const { return myInput; }

private:
	bool myStartGame = false;
	Tga::Vector2f myScreenResolution;

	ThreadingManager myThreadingManager;
	RenderCommand myRenderCommand;
	UIManager myUIManager;

	Input* myInput;
	Player myPlayer;
	EnemySpawner myEnemySpawner;

	std::vector<std::unique_ptr<Entity>> myEntities;

	std::vector<std::unique_ptr<ParticleSystem>> myParticleSystems;
	std::vector<std::unique_ptr<ParticleSystem>> myPendingParticleSystems;
};
