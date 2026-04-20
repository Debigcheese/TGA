#include "Camera.h"
#include <cmath>

bool Camera::Initialize(float aHorizontalFoVDegrees, Vector2f aResolution, float aNearPlane, float aFarPlane)
{
	const float hFovRad = aHorizontalFoVDegrees * FMath::DegToRad;

	// Projection matrix (horizontal FoV, DirectX convention, z=0 at near plane)
	// xScale = 1 / tan(hFov/2)
	// yScale = (w/h) * xScale   (aspect correction)
	const float xScale = 1.0f / std::tanf(hFovRad * 0.5f);
	const float yScale = (aResolution.x / aResolution.y) * xScale;
	const float Q = aFarPlane / (aFarPlane - aNearPlane);

	myProjection = Matrix4x4f(); // identity to start

	myProjection(1, 1) = xScale;
	myProjection(2, 2) = yScale;
	myProjection(3, 3) = Q;
	myProjection(3, 4) = 1.0f;
	myProjection(4, 3) = -Q * aNearPlane;
	myProjection(4, 4) = 0.0f;

	// Start camera at origin, looking forward (+Z)
	myCameraToWorld = Matrix4x4f();

	return true;
}

Matrix4x4f Camera::GetWorldToClipMatrix() const
{
	// worldToView = inverse of cameraToWorld (fast inverse for affine matrices)
	// worldToClip = worldToView * projection
	return Matrix4x4f::GetFastInverse(myCameraToWorld) * myProjection;
}

Vector3f Camera::GetForward() const
{
	// Row 3 of the camera-to-world matrix = forward axis
	return Vector3f(myCameraToWorld(3, 1), myCameraToWorld(3, 2), myCameraToWorld(3, 3));
}

Vector3f Camera::GetRight() const
{
	// Row 1 = right axis
	return Vector3f(myCameraToWorld(1, 1), myCameraToWorld(1, 2), myCameraToWorld(1, 3));
}

Vector3f Camera::GetPosition() const
{
	return Vector3f(myCameraToWorld(4, 1), myCameraToWorld(4, 2), myCameraToWorld(4, 3));
}

void Camera::SetPosition(const Vector3f& aPosition)
{
	myCameraToWorld(4, 1) = aPosition.x;
	myCameraToWorld(4, 2) = aPosition.y;
	myCameraToWorld(4, 3) = aPosition.z;
}

void Camera::SetRotation(float aPitchRad, float aYawRad)
{
	// Build rotation from pitch (X) and yaw (Y), then write into the
	// rotation part of cameraToWorld while preserving position.
	Vector3f position = GetPosition();

	Matrix4x4f pitchMatrix = Matrix4x4f::CreateRotationAroundX(aPitchRad);
	Matrix4x4f yawMatrix = Matrix4x4f::CreateRotationAroundY(aYawRad);
	Matrix4x4f rotation = pitchMatrix * yawMatrix;

	// Copy rotation rows, restore translation row
	for (int row = 1; row <= 3; ++row)
		for (int col = 1; col <= 4; ++col)
			myCameraToWorld(row, col) = rotation(row, col);

	SetPosition(position);
}