#pragma once
#include <functional>

#include "Component.h"
#include "tge/Graphics/TextureResource.h"

enum class HealthState
{
	None,
	Alive,
	Dead,
	Destroy
};

class HealthComponent : public Component
{
	using DeathCallBack = std::function<void(Entity*)>;

public:
	HealthComponent();
	~HealthComponent() override;

	void OnAdded() override;
	void Update(float aDeltaTime) override;
	void UpdateDeathAnimation(float aDeltaTime);

	//HEALTH COMP
	HealthState& GetHealthState() { return myHealthState; }
	void OnTakeDamage(int aDamage);
	void SetOnDeath(std::function<void(Entity*)> aCallBack) { myOnDeath = aCallBack; }
	bool GetIsDead() const { return myHealthState == HealthState::Dead || myHealthState == HealthState::Destroy; }

private:
	void OnDeath();

	HealthState myHealthState;
	DeathCallBack myOnDeath;

	int myHealthPoints = 1;

	float myTimeBeforeDestroy = 0.0f;
	static constexpr int DEATH_TEXTURE_SIZE = 4;
	Tga::TextureResource* myDeathTextures[DEATH_TEXTURE_SIZE];
};
