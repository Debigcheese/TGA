#pragma once
#include "Component.h"
#include "tge/math/Vector2.h"

struct MovementData
{
	Tga::Vector2f direction;
	Tga::Vector2f velocity;
	float speed;
	float gravity = 1.0f;
};

class MovementComponent : public Component
{
public:
	MovementComponent() = default;
	MovementComponent(const MovementComponent& aOther);
	~MovementComponent() override;

	void Update(float aDeltaTime) override;
	void OnAdded() override;

	//MOVEMENT COMP
	void SetMovement(const MovementData& aMovement) { myMovement = aMovement; }
	void SetDirection(const Tga::Vector2f& aDirection) { myMovement.direction = aDirection; }
	void SetSpeed(const float aSpeed) { myMovement.speed = aSpeed; }
	void SetGravity(const float aGravity) { myMovement.gravity = aGravity; }
	const MovementData& GetMovement() const { return myMovement; }

	//EXTRA
	void SetVelocityBasedRotation(bool aVelocityRotation) { myVelocityBasedRotation = aVelocityRotation; }
	bool CheckOutOfBounds() const;

private:
	//MOVEMENT COMP
	void ApplyMovement(float aTimeDelta);
	void ApplyRotation();

	MovementData myMovement;
	bool myVelocityBasedRotation = true;
};
