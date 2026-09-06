#pragma once
#include "CommonUtilities/math/Matrix4x4.h"
#include "CommonUtilities/math/Vector3.h"

Tga::Matrix4x4f BuildBoxTransform(const Tga::Vector3f& aPosition, const Tga::Vector3f& aScale);
Tga::Matrix4x4f BuildAimedTransform(const Tga::Vector3f& aPosition, const Tga::Vector3f& aDirection, float aScale);
