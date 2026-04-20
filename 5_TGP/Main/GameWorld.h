#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Camera/Camera.h"
#include "Model/Mesh.h"
#include "Camera/CameraController.h"
#include "GameObject/GameObjectFactory.h"
#include <vector>

#include "CommonUtilities/input/InputManager.h"
#include "CommonUtilities/math/vector3.h"
#include "CommonUtilities/math/Matrix4x4.h"

using Microsoft::WRL::ComPtr;

namespace Tga
{
	class InputManager;
}

// Must match cbuffer FrameBuffer : register(b0) in shaders
struct FrameBufferData
{
	Matrix4x4f worldToClipMatrix; // 64 bytes
	float totalTime;         // 4 bytes
	float padding[3];        // 12 bytes, keeps 16-byte alignment
};

// Must match cbuffer ObjectBuffer : register(b1) in shaders
struct ObjectBufferData
{
	Matrix4x4f modelToWorldMatrix; // 64 bytes
};

class GameWorld
{
public:
	GameWorld() = default;

	bool Init();
	void Update(float aDeltaTime);
	void Render();

private:
	bool CreateConstantBuffers();
	void UpdateFrameBuffer();
	void UpdateObjectBuffer(const Matrix4x4f& aModelToWorld);

	CameraController myCameraController;
	Camera myCamera;

	std::vector<GameObject>  myObjects;

	ComPtr<ID3D11Buffer> myFrameBuffer;
	ComPtr<ID3D11Buffer> myObjectBuffer;

	Tga::InputManager* myInputManager = nullptr;
	float myTotalTime{};
};