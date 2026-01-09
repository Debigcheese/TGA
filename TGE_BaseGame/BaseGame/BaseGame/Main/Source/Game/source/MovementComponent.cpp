#include "MovementComponent.h"

#include <algorithm>

#include "Entity.h"

MovementComponent::MovementComponent(const MovementComponent& aOther) :
	myMovement(aOther.myMovement),
	myVelocityBasedRotation(
		aOther.myVelocityBasedRotation)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(float aDeltaTime)
{
	Component::Update(aDeltaTime);

	ApplyMovement(aDeltaTime);
	ApplyRotation();
}

void MovementComponent::OnAdded()
{
	Component::OnAdded();
}

void MovementComponent::ApplyMovement(float aTimeDelta)
{
	const float speed = myMovement.speed;

	myMovement.direction.x = std::clamp(myMovement.direction.x, -1.0f, 1.0f);
	myMovement.direction.y = std::clamp(myMovement.direction.y, -1.0f, 1.0f);

	myMovement.direction.y -= myMovement.gravity * aTimeDelta;
	myMovement.velocity = myMovement.direction * speed * aTimeDelta;

	myOwner->GetSpriteInstance().myPosition += myMovement.velocity;
}

void MovementComponent::ApplyRotation()
{
	if (!myVelocityBasedRotation)
	{
		return;
	}

	if (myMovement.velocity.x != 0.0f || myMovement.velocity.y != 0.0f)
	{
		float angle = std::atan2(std::abs(myMovement.velocity.y), std::abs(myMovement.velocity.x));
		myOwner->GetSpriteInstance().myRotation = angle;
	}
}

bool MovementComponent::CheckOutOfBounds() const
{
	const auto& position = myOwner->GetPosition();
	const auto& resolution = myOwner->GetResolution();

	if (position.x < 0 || position.x > resolution.x)
	{
		return true;
	}
	if (position.y < 0 || position.y > resolution.y)
	{
		return true;
	}
	return false;
}
