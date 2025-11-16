#include "Ship.h"

#include "tge/Engine.h"
#include "tge/drawers/DebugDrawer.h"

Ship::Ship()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	myScreenResolution = {(float)intResolution.x, (float)intResolution.y};

	myInput = &globalInputHandler;
	myPosition = {myScreenResolution.x / 2, myScreenResolution.y / 2};
}

void Ship::Update(float aTimeDelta)
{
	auto* input = myInput;

	Vector2 directionVector = {0.0f, 0.0f};
	if (input->IsKeyDown(VK_UP))
	{
		directionVector = myUnitVector;
	}
	if (input->IsKeyDown(VK_DOWN))
	{
		directionVector = -myUnitVector;
	}

	constexpr float accelerationScalar = 200.0f;

	myVelocity = myVelocity + accelerationScalar * directionVector * aTimeDelta;
	myPosition = myPosition + myVelocity * aTimeDelta;

	float rotationInput = 0.0f;
	if (input->IsKeyDown(VK_LEFT))
	{
		rotationInput = 1.0f;
	}
	if (input->IsKeyDown(VK_RIGHT))
	{
		rotationInput = -1.0f;
	}

	constexpr float baseRotationSpeed = 2.5f;
	float rotationSpeed = baseRotationSpeed * rotationInput;

	myAngle = myAngle + rotationSpeed * aTimeDelta;
	myUnitVector = {cosf(myAngle), sinf(myAngle)};

	HandleBounds();
}

void Ship::Render() const
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::DebugDrawer& debugDrawer = engine.GetDebugDrawer();

	Vector2 center = myPosition;
	Vector2 forward = myUnitVector;
	Vector2 right(forward.y, -forward.x);

	float length = 50.f;
	float halfWidth = 20.f;
	float backOffset = 20.f;

	Vector2 nose = center + forward * length;
	Vector2 tail = center - forward * backOffset;
	Vector2 left = tail - right * halfWidth;
	Vector2 rightV = tail + right * halfWidth;

	debugDrawer.DrawLine(nose.ToTga(), left.ToTga());
	debugDrawer.DrawLine(nose.ToTga(), rightV.ToTga());
	debugDrawer.DrawLine(left.ToTga(), rightV.ToTga());
}

void Ship::HandleBounds()
{
	if (myPosition.y > myScreenResolution.y)
	{
		myPosition = {myPosition.x, 0};
	}
	else if (myPosition.y < 0)
	{
		myPosition = {myPosition.x, myScreenResolution.y};
	}
	if (myPosition.x > myScreenResolution.x)
	{
		myPosition = {0, myPosition.y};
	}
	else if (myPosition.x < 0)
	{
		myPosition = {myScreenResolution.x, myPosition.y};
	}
}
