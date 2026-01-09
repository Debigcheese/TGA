#pragma once
#include <functional>
#include <vector>

#include "Entity.h"
#include "Paratrooper.h"
#include "tge/math/Vector2.h"
#include "tge/sprite/sprite.h"

struct ParticleSettings
{
	int count;
	float lifeTime = 2.0f;
	std::string texturePath;
	MovementData movementData;
	Transform transform;
};

enum class ParticlePreset
{
	CircleSpread,
};

class ParticleSystem
{
	using OnDeath = std::function<void()>;

public:
	ParticleSystem();
	~ParticleSystem();

	void Init(ParticlePreset aPreset);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);
	void Play();

	void SetTransform(const Transform& aTransform) { myParticleSetting.transform = aTransform; }
	void SetPosition(const Tga::Vector2f& aPosition) { myParticleSetting.transform.position = aPosition; }
	void SetOnDeath(const OnDeath& aCallback) { myOnDeathCallback = aCallback; }
	bool GetIsActive() const { return myIsActive; }

	std::vector<std::unique_ptr<Entity>>& GetParticles() { return myEntities; }

private:
	Tga::SpriteSharedData mySharedData;
	Tga::Vector2f myResolution;

	ParticlePreset myPreset;
	ParticleSettings myParticleSetting;
	std::vector<std::unique_ptr<Entity>> myEntities;
	OnDeath myOnDeathCallback;

	bool myIsActive = false;
};
