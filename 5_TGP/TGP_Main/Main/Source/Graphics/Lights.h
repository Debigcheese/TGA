#pragma once
#include <cmath>
#include "CommonUtilities/math/vector3.h"

// How many lights the shader can handle in ONE draw call.
// If an object is hit by more than this, we draw it again.
static constexpr int MAX_LIGHTS_PER_PASS = 8;

struct PointLight
{
	Tga::Vector3f position = { 0.0f, 0.0f, 0.0f };
	Tga::Vector3f color = { 1.0f, 1.0f, 1.0f };
	float intensity = 30.0f;
	float range = 15.0f;

	// animation only
	Tga::Vector3f orbitCenter = { 0.0f, 0.0f, 0.0f };
	float orbitRadius = 6.0f;
	float orbitSpeed = 0.5f;
	float phase = 0.0f;
};

struct SpotLight
{
	Tga::Vector3f position = { 0.0f, 0.0f, 0.0f };
	Tga::Vector3f direction = { 0.0f, -1.0f, 0.0f };
	Tga::Vector3f color = { 1.0f, 1.0f, 1.0f };
	float intensity = 40.0f;
	float range = 20.0f;
	float innerAngle = 0.25f; // radians. full brightness inside this cone
	float outerAngle = 0.45f; // radians. fades to black out here

	// animation only
	Tga::Vector3f orbitCenter = { 0.0f, 0.0f, 0.0f };
	float orbitRadius = 8.0f;
	float orbitSpeed = 0.4f;
	float phase = 0.0f;
};

//  "this light hits this object". Type + which index + how far away.
struct LightRef
{
	bool isSpot;
	int index;
	float distance;
};

//  must match the HLSL structs
struct PointLightGPU
{
	float position[3];
	float range;
	float color[3];
	float intensity;
};

static_assert(sizeof(PointLightGPU) == 32, "PointLightGPU must be 32 bytes");

struct SpotLightGPU
{
	float position[3];
	float range;
	float direction[3];
	float cosOuter;
	float color[3];
	float intensity;
	float cosInner;
	float padding[3];
};

static_assert(sizeof(SpotLightGPU) == 64, "SpotLightGPU must be 64 bytes");
