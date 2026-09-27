#include "TransformUtils.h"
#include <cmath>

using Tga::Matrix4x4f;
using Tga::Vector3f;

Matrix4x4f BuildAimedTransform(const Vector3f& aPosition,
                               const Vector3f& aDirection,
                               float aScale)
{
	Vector3f y = aDirection.GetNormalized();
	Vector3f ref = (fabsf(y.y) > 0.99f) ? Vector3f{1, 0, 0} : Vector3f{0, 1, 0};
	Vector3f x = ref.Cross(y).GetNormalized();
	Vector3f z = y.Cross(x);

	Matrix4x4f m = Matrix4x4f::CreateIdentityMatrix();
	m(1, 1) = x.x * aScale;
	m(1, 2) = x.y * aScale;
	m(1, 3) = x.z * aScale;
	m(2, 1) = y.x * aScale;
	m(2, 2) = y.y * aScale;
	m(2, 3) = y.z * aScale;
	m(3, 1) = z.x * aScale;
	m(3, 2) = z.y * aScale;
	m(3, 3) = z.z * aScale;
	m(4, 1) = aPosition.x;
	m(4, 2) = aPosition.y;
	m(4, 3) = aPosition.z;
	return m;
}

Matrix4x4f BuildBoxTransform(const Vector3f& aPosition, const Vector3f& aScale)
{
	Matrix4x4f m = Matrix4x4f::CreateIdentityMatrix();
	m(1, 1) = aScale.x;
	m(2, 2) = aScale.y;
	m(3, 3) = aScale.z;
	m(4, 1) = aPosition.x;
	m(4, 2) = aPosition.y;
	m(4, 3) = aPosition.z;
	return m;
}
