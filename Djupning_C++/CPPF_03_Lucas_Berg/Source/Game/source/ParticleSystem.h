#pragma once
#include <functional>
#include <vector>

#include "GameObject.h"
#include "Paratrooper.h"
#include "tge/math/Vector2.h"
#include "tge/sprite/sprite.h"

struct EmitterSetting
{
	int count;
	float lifeTime = 2.0f;
	std::string texturePath;
};

class ParticleSystem
{
	using OnDeath = std::function<void()>;

public:
	ParticleSystem();
	~ParticleSystem();

	void Init(const EmitterSetting& aSetting);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);

	void SetPosition(const Tga::Vector2f aPosition) { mySpriteInstance.myPosition = aPosition; }
	void Play();
	void SetOnDeath(const OnDeath& aCallback) { myOnDeathCallback = aCallback; };

	bool GetIsActive() const { return myIsActive; }

private:
	Tga::Sprite2DInstanceData mySpriteInstance;
	Tga::SpriteSharedData mySharedData;
	Tga::Vector2f myResolution;

	EmitterSetting myEmitterSetting;
	std::vector<GameObject> myGameObjects;
	OnDeath myOnDeathCallback;

	bool myIsActive = false;
	State myState;
};
