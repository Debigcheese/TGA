#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Camera/Camera.h"
#include "Model/Mesh.h"
#include "Model/TerrainMesh.h"
#include "Camera/CameraController.h"
#include "GameObject/GameObjectFactory.h"
#include "Shader/Shader.h"
#include <vector>
#include "Model/Texture.h"

#include "CommonUtilities/input/InputManager.h"
#include "CommonUtilities/math/vector3.h"
#include "CommonUtilities/math/Matrix4x4.h"

using Microsoft::WRL::ComPtr;

namespace Tga
{
	class InputManager;
}

// Must match cbuffer FrameBuffer: register(b0) in shaders
struct FrameBufferData
{
	Matrix4x4f worldToClipMatrix;
	float      totalTime;
	float      padding[3];
	Vector3f   cameraPosition;
	float      cameraPad;
};

// Must match cbuffer ObjectBuffer: register(b1) in shaders
struct ObjectBufferData
{
	Matrix4x4f modelToWorldMatrix;
};

// Must match cbuffer LightBuffer : register(b2)
struct LightBufferData
{
	float dirLightDir[3];   float lp1;
	float dirLightColor[3]; float lp2;
	float ambientSky[3];    float lp3;
	float ambientGround[3]; float lp4;
};

class GameWorld
{
public:
	GameWorld() = default;

	bool Init();
	void Update(float aDeltaTime);
	void Render();

private:
	//doesnt belong in gameworld
	bool CreateConstantBuffers();
	bool CreateTextures(ID3D11Device* device);
	void UpdateFrameBuffer();
	void UpdateObjectBuffer(const Matrix4x4f& m);
	void UpdateLightBuffer();

	CameraController myCameraController;
	Camera myCamera;

	std::vector<GameObject>  myObjects;
	TerrainMesh myTerrain;
	Shader myTerrainShader;

	Texture myFileTexture;
	Texture myProceduralTexture;

	ComPtr<ID3D11Buffer> myFrameBuffer;
	ComPtr<ID3D11Buffer> myObjectBuffer;
	ComPtr<ID3D11Buffer> myLightBuffer;
	ComPtr<ID3D11SamplerState> mySampler;

	Tga::InputManager* myInputManager = nullptr;
	float myTotalTime{};
	float myDayAngle = 0.0f;
};