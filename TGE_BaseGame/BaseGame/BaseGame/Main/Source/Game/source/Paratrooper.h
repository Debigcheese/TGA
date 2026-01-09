#pragma once
#include "Enemy.h"
#include "tge/math/Vector2.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"
#include "CommonUtilities/InputHandler.h"
#include "Component.h"
#include "Entity.h"
#include "MovementComponent.h"

enum State
{
	Falling = 0,
	Parachuting = 1,
	Grounded = 2,
	Scored = 3,
	Dead = 4,
	Destroy = 5
};

class Paratrooper : public Component
{
	using ReachedPlayerCallback = std::function<void(Paratrooper*)>;
	using OpenParachuteCallback = std::function<void(Entity*)>;
	using LandedCallback = std::function<void(Entity*)>;

public:
	Paratrooper() = default;
	~Paratrooper() override;
	void OnAdded() override;

	void Update(float aTimeDelta) override;

	void SetParachuteDestroyed();
	bool HasParachute() const { return myState == State::Parachuting; }
	bool HasLanded() const;

	void SetParachute(Entity* aParachute) { myParachute = aParachute; }
	Entity* GetParachute() const { return myParachute; }

	void SetOnReachedPlayer(ReachedPlayerCallback aCallback) { myOnReachedPlayer = aCallback; }
	void SetOnOpenParachute(OpenParachuteCallback aCallback) { myOnParachuteCallback = aCallback; }
	void SetOnLanded(LandedCallback aCallback) { myOnLandedCallback = aCallback; }

	bool HasReachedPlayer() const;

	void SetState(State aState) { myState = aState; }
	State GetState() const { return myState; }
	bool GetLeftSide() const { return myLeftSide; }

	void IncrementDistanceOffset(float aDistanceOffset) { myDistanceOffset += aDistanceOffset; }
	void ResetDistanceOffset() { myDistanceOffset = 40.0f; }

	Tga::Vector2f GetPosition() const { return myOwner->GetPosition(); }

private:
	static constexpr int TEXTURE_SIZE = 3;
	Tga::TextureResource* myTextures[TEXTURE_SIZE];

	std::shared_ptr<MovementComponent> myMovementComp;
	Entity* myParachute = nullptr;

	ReachedPlayerCallback myOnReachedPlayer;
	OpenParachuteCallback myOnParachuteCallback;
	LandedCallback myOnLandedCallback;
	State myState = State::Falling;

	bool myForgotParachuteAtHome = false;
	float myDeathDuration = 1.5f;

	float myTimeToParachute = 0.5f;
	float myParachuteTimer = 0.0f;

	float myDistanceOffset = 40.0f;

	bool myLeftSide = false;
};
