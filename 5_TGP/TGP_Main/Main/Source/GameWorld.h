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
#include "Cubemap.h"
#include "Graphics/RenderTarget.h"

#include "CommonUtilities/input/InputManager.h"
#include "CommonUtilities/math/vector3.h"
#include "CommonUtilities/math/Matrix4x4.h"

using Microsoft::WRL::ComPtr;

namespace Tga
{
	class InputManager;
}

struct ReflectionBufferData
{
	float resolution[2];
	float waterHeight;
	float reflectMode; // 1.0 = reflect, 0.0 = normal
};

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
	float dirLightColor[3]; float dirLightIntensity;  
	float ambientColor[3];  float ambientIntensity;
	int   numEnvMapMipLevels;
	float pad0, pad1, pad2;
	float cameraPosition[3]; float camPad;
};

struct DirectionalLightConfig
{
	float daySpeed = 0.1f;

	float sunDirZ = -0.3f;

	float dayShift = 1.6f;
	float dayRange = 1.6f;

	float dirStrengthMin = 1.5f;
	float dirStrengthMax = 2.3f;
	float dirColorR = 1.00f;
	float dirColorG = 0.95f;
	float dirColorB = 0.85f;

	float ambSkyMinR = 0.20f, ambSkyMaxR = 0.25f;
	float ambSkyMinG = 0.25f, ambSkyMaxG = 0.30f;
	float ambSkyMinB = 0.30f, ambSkyMaxB = 0.35f;

	float ambGndMinR = 0.2f, ambGndMaxR = 0.21f;
	float ambGndMinG = 0.23f, ambGndMaxG = 0.25f;
	float ambGndMinB = 0.25f, ambGndMaxB = 0.27f;
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
	void UpdateFrameBuffer(const Matrix4x4f& aWorldToClip);
	void UpdateReflectionBuffer(float px, float py, float pz, float pw);
	void BindTerrainTextures(ID3D11DeviceContext* context);
	
	void UpdateObjectBuffer(const Matrix4x4f& m);
	void UpdateLightBuffer();

	// Helper to avoid repeating the stbi boilerplate
	bool LoadTextureFromFile(ID3D11Device* device, ID3D11DeviceContext* context, const char* path, Texture& tex, bool srgb);

	CameraController myCameraController;
	Camera myCamera;

	std::vector<GameObject>  myObjects;

	TerrainMesh myTerrain;
	Shader myTerrainShader;
	DirectionalLightConfig myLightConfig;
	float myDayAngle = 1.0f;

	Texture myGrassColor, myRockColor, mySnowColor;
	Texture myGrassNormal, myRockNormal, mySnowNormal;

	Texture myGrassMaterial, myRockMaterial, mySnowMaterial;
	Cubemap myEnvironmentCubemap;

	Texture myFileTexture;
	Texture myProceduralTexture;

	ComPtr<ID3D11Buffer> myFrameBuffer;
	ComPtr<ID3D11Buffer> myObjectBuffer;
	ComPtr<ID3D11Buffer> myLightBuffer;
	ComPtr<ID3D11SamplerState> mySampler;
	
	//water
	RenderTarget myReflectionRT;
	GameObject   myWaterObject;
	ComPtr<ID3D11Buffer> myReflectionBuffer;
	float myWaterHeight = -5.0f;
	ComPtr<ID3D11RasterizerState> myFrontFaceCullingRasterizerState;

	Tga::InputManager* myInputManager = nullptr;
	float myTotalTime{};
};