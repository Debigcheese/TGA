#pragma once
#include "Enemy.h"

class Bomb : public Enemy
{
	using ExplodeCallback = std::function<void()>;

public:
	Bomb();
	~Bomb() override;

	void Update(float aTimeDelta) override;

	void SetOnExplode(ExplodeCallback aCallback) { myOnExplode = aCallback; }
	bool GetShouldExplode() const { return myShouldExplode; }

private:
	Tga::Sprite2DInstanceData myBombInstance;
	Tga::SpriteSharedData myBombData;
	bool myShouldExplode = false;

	ExplodeCallback myOnExplode;
};
