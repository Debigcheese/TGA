#pragma once
#include "Enemy.h"
#include "tge/math/Vector2.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"
#include "CommonUtilities/InputHandler.h"

enum State
{
	Falling = 0,
	Parachuting = 1,
	Grounded = 2,
	Scored = 3,
	Dead = 4,
	Destroy = 5
};

class Paratrooper : public Enemy
{
	using ReachedPlayerCallback = std::function<void(Paratrooper*)>;

public:
	Paratrooper();
	~Paratrooper() override;

	void Update(float aTimeDelta) override;
	void SetOnReachedPlayer(ReachedPlayerCallback aCallback) { myOnReachedPlayer = aCallback; }
	bool HasReachedPlayer() const;

	void SetState(State aState) { myState = aState; }
	State GetState() const { return myState; }

	void IncrementDistanceOffset(float aDistanceOffset) { myDistanceOffset += aDistanceOffset; }
	void ResetDistanceOffset() { myDistanceOffset = 40.0f; }

	Tga::Vector2f GetParachuteSize() const { return mySpriteInstance.mySize; }
	Tga::Vector2f GetParachutePosition() const;

private:
	static constexpr int TEXTURE_SIZE = 3;
	Tga::TextureResource* myTextures[TEXTURE_SIZE];

	ReachedPlayerCallback myOnReachedPlayer;
	State myState = State::Falling;

	bool myForgotParachuteAtHome = false;
	float myDeathDuration = 1.5f;

	float myTimeToParachute = 0.5f;
	float myParachuteTimer = 0.0f;

	float myDistanceOffset = 40.0f;
};
