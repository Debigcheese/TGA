#pragma once
#include "Camera.h"
#include "CommonUtilities/input/InputManager.h"

class CameraController
{
public:
	void Initialize(Camera* aCamera, Tga::InputManager* aInputManager);
	void Update(float aDeltaTime);

private:
	Camera* myCamera = nullptr;
	Tga::InputManager* myInputManager = nullptr;

	float myPitch = 0.0f;
	float myYaw = 0.0f;
	float mySpeed = 5.0f;

	static constexpr float DefaultCameraSpeed = 5.0f;
	static constexpr float MinCameraSpeed = 1.0f;
	static constexpr float MaxCameraSpeed = 25.0f;

	static constexpr float CameraRotSpeed = 0.13f;
};