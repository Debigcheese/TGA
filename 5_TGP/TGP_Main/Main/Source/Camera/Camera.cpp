#include "Camera.h"
#include <cmath>

bool Camera::Initialize(float aHorizontalFoVDegrees, Vector2f aResolution, float aNearPlane, float aFarPlane)
{
    const float hFovRad = aHorizontalFoVDegrees * FMath::DegToRad;

    const float xScale = 1.0f / std::tanf(hFovRad * 0.5f);
    const float yScale = (aResolution.x / aResolution.y) * xScale;
    const float Q = aFarPlane / (aFarPlane - aNearPlane);

    myProjection = Matrix4x4f();

    myProjection(1, 1) = xScale;
    myProjection(2, 2) = yScale;
    myProjection(3, 3) = Q;
    myProjection(3, 4) = 1.0f;
    myProjection(4, 3) = -Q * aNearPlane;
    myProjection(4, 4) = 0.0f;

    myCameraToWorld = Matrix4x4f();

    return true;
}

Matrix4x4f Camera::GetWorldToClipMatrix() const
{
    return Matrix4x4f::GetFastInverse(myCameraToWorld) * myProjection;
}

Matrix4x4f Camera::GetViewMatrix() const
{
    return Matrix4x4f::GetFastInverse(myCameraToWorld);
}

Vector3f Camera::GetForward() const
{
    return Vector3f(myCameraToWorld(3, 1), myCameraToWorld(3, 2), myCameraToWorld(3, 3));
}

Vector3f Camera::GetRight() const
{
    return Vector3f(myCameraToWorld(1, 1), myCameraToWorld(1, 2), myCameraToWorld(1, 3));
}

// NY: Up-vektor
Vector3f Camera::GetUp() const
{
    return Vector3f(myCameraToWorld(2, 1), myCameraToWorld(2, 2), myCameraToWorld(2, 3));
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