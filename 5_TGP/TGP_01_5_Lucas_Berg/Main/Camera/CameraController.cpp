#include "CameraController.h"

static constexpr int KEY_W = 0x57;
static constexpr int KEY_A = 0x41;
static constexpr int KEY_S = 0x53;
static constexpr int KEY_D = 0x44;
static constexpr int KEY_Q = 0x51;
static constexpr int KEY_E = 0x45;

void CameraController::Initialize(Camera* aCamera, Tga::InputManager* aInputManager)
{
	myCamera = aCamera;
	myInputManager = aInputManager;
}

void CameraController::Update(float aDeltaTime)
{
	Vector3f movement = {};

	if (myInputManager->IsKeyHeld(KEY_W))
		movement = movement + myCamera->GetForward() * CameraSpeed * aDeltaTime;
	if (myInputManager->IsKeyHeld(KEY_S))
		movement = movement + myCamera->GetForward() * (-CameraSpeed * aDeltaTime);
	if (myInputManager->IsKeyHeld(KEY_D))
		movement = movement + myCamera->GetRight() * CameraSpeed * aDeltaTime;
	if (myInputManager->IsKeyHeld(KEY_A))
		movement = movement + myCamera->GetRight() * (-CameraSpeed * aDeltaTime);

	if (myInputManager->IsKeyHeld(KEY_E))
		movement = movement + Vector3f(0, 1, 0) * CameraSpeed * aDeltaTime;
	if (myInputManager->IsKeyHeld(KEY_Q))
		movement = movement + Vector3f(0, -1, 0) * CameraSpeed * aDeltaTime;

	myCamera->SetPosition(myCamera->GetPosition() + movement);

	if (!myInputManager->IsKeyHeld(VK_RBUTTON))
		return;

	Tga::Vector2f delta = myInputManager->GetMouseDelta();
	myPitch += delta.y * CameraRotSpeed;
	myYaw += delta.x * CameraRotSpeed;

	myCamera->SetRotation(myPitch, myYaw);
}