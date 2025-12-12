#pragma once
#include "Enemy.h"

enum SpawnTrooper
{
	NotSpawned = 0,
	ShouldSpawn = 1,
	HasSpawned = 2,
	NeverSpawn = 3
};

class Helicopter : public Enemy
{
	using SpawnTrooperCallback = std::function<void(const Tga::Vector2f& aPosition)>;

public:
	Helicopter();
	~Helicopter() override;

	void Update(float aTimeDelta) override;
	void UpdateAnimation(float aTimeDelta);

	void SetOnSpawnTrooper(SpawnTrooperCallback aCallback) { myOnSpawnTrooper = aCallback; }
	void SetSpawnTrooper(SpawnTrooper aSpawnTrooper) { mySpawnTrooper = aSpawnTrooper; }

	SpawnTrooper GetSpawnTrooper() const { return mySpawnTrooper; }

private:
	static constexpr int TEXTURE_SIZE = 3;
	Tga::TextureResource* myTextures[TEXTURE_SIZE];
	float myAnimTimer = 0;

	float myTimeBeforeParatrooper = 0.0f;
	SpawnTrooper mySpawnTrooper = SpawnTrooper::NotSpawned;
	SpawnTrooperCallback myOnSpawnTrooper;
};
