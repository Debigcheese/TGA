#pragma once
#include "CommonUtilities/math/Matrix4x4.h"
#include "CommonUtilities/math/vector2.h"

using namespace Tga;

class Camera
{
public:
	bool Initialize(float aHorizontalFoVDegrees, Vector2f aResolution, float aNearPlane, float aFarPlane);

	Matrix4x4f& GetCameraToWorldMatrix() { return myCameraToWorld; }
	Matrix4x4f GetWorldToClipMatrix() const;

	// Helpers will be used by camera controller 
	Vector3f GetForward() const;
	Vector3f GetRight() const;
	Vector3f GetPosition() const;
	void SetPosition(const Vector3f& aPosition);
	void SetRotation(float aPitchRad, float aYawRad);

private:
	Matrix4x4f myCameraToWorld;
	Matrix4x4f myProjection;
};