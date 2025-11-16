#pragma once
#include "Vector2.h"
#include "CommonUtilities/InputHandler.h"

using Input = CommonUtilities::InputHandler;

template <typename T>
using Vector2 = CommonUtilities::Vector2<T>;

class Ship
{
public:
	Ship();

	void Update(float aTimeDelta);
	void Render() const;

	void HandleBounds();

private:
	Input* myInput;

	Vector2<float> myScreenResolution;
	Vector2<float> myVelocity;
	Vector2<float> myPosition;
	Vector2<float> myUnitVector;

	float myAngle;
};
