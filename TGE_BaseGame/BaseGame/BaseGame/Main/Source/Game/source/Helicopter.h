#pragma once
#include <functional>

#include "Component.h"
#include "tge/Graphics/TextureResource.h"
#include "tge/math/Vector2.h"

enum SpawnTrooper
{
	NotSpawned = 0,
	ShouldSpawn = 1,
	HasSpawned = 2,
	NeverSpawn = 3
};

class Helicopter : public Component
{
	using SpawnTrooperCallback = std::function<void(const Tga::Vector2f& aPosition)>;

public:
	Helicopter() = default;
	~Helicopter() override;
	void OnAdded() override;

	void Update(float aTimeDelta) override;
	void UpdateAnimation(float aTimeDelta);

	void SetOnSpawnTrooper(SpawnTrooperCallback aCallback) { myOnSpawnTrooper = aCallback; }
	void SetSpawnTrooper(SpawnTrooper aSpawnTrooper) { mySpawnTrooper = aSpawnTrooper; }

	SpawnTrooper GetSpawnTrooper() const { return mySpawnTrooper; }

private:
	static constexpr int TEXTURE_SIZE_CHOPPER = 2;
	Tga::TextureResource* myTexturesChopper[TEXTURE_SIZE_CHOPPER];
	float myAnimTimerChopper = 0;

	float myTimeBeforeParatrooper = 0.0f;
	SpawnTrooper mySpawnTrooper = SpawnTrooper::NotSpawned;
	SpawnTrooperCallback myOnSpawnTrooper;

	bool myLeftSide;
};
