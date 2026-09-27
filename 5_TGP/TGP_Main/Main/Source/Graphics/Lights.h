#pragma once
#include <cmath>
#include "CommonUtilities/math/vector3.h"

static constexpr int MAX_LIGHTS_PER_PASS = 8;

struct PointLight
{
	Tga::Vector3f position = { 0.0f, 0.0f, 0.0f };
	Tga::Vector3f color = { 1.0f, 1.0f, 1.0f };
	float intensity = 6.0f;
	float range = 20.0f;

	Tga::Vector3f orbitCenter = {0.0f, 0.0f, 0.0f};
	float orbitRadius = 6.0f;
	float orbitSpeed = 0.5f;
	float phase = 0.0f;
};

struct SpotLight
{
	Tga::Vector3f position = { 0.0f, 0.0f, 0.0f };
	Tga::Vector3f direction = { 0.0f, -1.0f, 0.0f };
	Tga::Vector3f color = { 1.0f, 1.0f, 1.0f };
	float intensity = 5.0f;
	float range = 20.0f;
	float innerAngle = 0.35f;
	float outerAngle = 0.65f;

	Tga::Vector3f orbitCenter = {0.0f, 0.0f, 0.0f};
	float orbitRadius = 8.0f;
	float orbitSpeed = 0.4f;
	float phase = 0.0f;
};

struct LightRef
{
	bool isSpot;
	int index;
	float distance;
};

struct PointLightGPU
{
	Tga::Vector3f position;
	float range;
	Tga::Vector3f color;
	float intensity;
};

static_assert(sizeof(PointLightGPU) == 32, "PointLightGPU must be 32 bytes");

struct SpotLightGPU
{
	Tga::Vector3f position;
	float range;
	Tga::Vector3f direction;
	float cosOuter;
	Tga::Vector3f color;
	float intensity;
	float cosInner;
	float padding[3];
};

static_assert(sizeof(SpotLightGPU) == 64, "SpotLightGPU must be 64 bytes");
