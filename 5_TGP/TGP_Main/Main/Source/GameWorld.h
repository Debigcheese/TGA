#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>
#include "Camera/Camera.h"
#include "Camera/CameraController.h"
#include "GameObject/GameObjectFactory.h"
#include "Graphics/Lights.h"
#include "Graphics/RenderTarget.h"
#include "Model/Mesh.h"
#include "Model/TerrainMesh.h"
#include "Model/Texture.h"
#include "Shader/Shader.h"
#include "Cubemap.h"

#include "CommonUtilities/math/vector3.h"
#include "CommonUtilities/math/Matrix4x4.h"

using Microsoft::WRL::ComPtr;

namespace Tga
{
	class InputManager;
}

struct FrameBufferData
{
	Matrix4x4f worldToClipMatrix;
	float totalTime;
	float padding[3];
	Vector3f cameraPosition;
	float cameraPad;
};

struct ObjectBufferData
{
	Matrix4x4f modelToWorldMatrix;
	Vector3f emissiveColor;
	float emissiveStrength;
};

struct LightBufferData
{
	Vector3f dirLightDirection;
	float pad0;
	Vector3f dirLightColor;
	float dirLightIntensity;
	Vector3f ambientColor;
	float ambientIntensity;
	Vector3f ambientGround;
	float pad1;
	Vector3f ambientSky;
	float pad2;
	int numEnvMapMipLevels;
	float pad3[3];
	Vector3f cameraPosition;
	float pad4;

	int numPointLights;
	int numSpotLights;
	int isAdditivePass;
	int pad5;

	PointLightGPU pointLights[MAX_LIGHTS_PER_PASS];
	SpotLightGPU spotLights[MAX_LIGHTS_PER_PASS];
};

static_assert(sizeof(LightBufferData) == 896, "LightBufferData size mismatch");

struct ReflectionBufferData
{
	float resolution[2];
	float waterHeight;
	float reflectMode;
};

struct DirectionalLightConfig
{
	Vector3f direction = {-0.4f, -1.0f, 0.3f};
	Vector3f color = {1.0f, 0.95f, 0.85f};
	float intensity = 0.18f;
	Vector3f ambientSky = {0.038f, 0.045f, 0.05f};
	Vector3f ambientGround = {0.031f, 0.037f, 0.04f};
};

struct ArenaPiece
{
	Matrix4x4f transform;
	Vector3f position;
	float radius;
};

class GameWorld
{
public:
	GameWorld() = default;
	~GameWorld();

	bool Init();
	void Update(float aDeltaTime);
	void Render();

private:
	bool CreateConstantBuffers();
	bool CreateRenderStates();
	bool LoadTextureFromFile(ID3D11Device* aDevice, ID3D11DeviceContext* aContext, const char* aPath, Texture& aTexture,
	                         bool anSRGB);

	void CreateObjects();
	void CreateArena();
	void CreateLights();
	void AnimateLights();

	void UpdateFrameBuffer(const Matrix4x4f& aWorldToClip);
	void UpdateObjectBuffer(const Matrix4x4f& aModelToWorld, const Vector3f& anEmissiveColor = {0, 0, 0},
	                        float anEmissiveStrength = 0.0f);
	void UpdateLightBuffer(const std::vector<LightRef>& someLights, bool anAdditivePass);
	void UpdateReflectionBuffer(float aResolutionX, float aResolutionY, float aWaterHeight, float aReflectMode);
	void BindTerrainTextures(ID3D11DeviceContext* aContext);

	std::vector<LightRef> CollectLightsForObject(const Vector3f& anObjectPosition, float anObjectRadius);
	void RenderPieceWithLights(ID3D11DeviceContext* aContext, GameObject& anObject, const Matrix4x4f& aTransform,
	                           const Vector3f& aWorldPosition, float aRadius);
	void RenderObjectWithLights(ID3D11DeviceContext* aContext, GameObject& anObject);
	void RenderArena(ID3D11DeviceContext* aContext);
	void RenderLightMarkers(ID3D11DeviceContext* aContext);

	Camera myCamera;
	CameraController myCameraController;

	ComPtr<ID3D11Buffer> myFrameBuffer;
	ComPtr<ID3D11Buffer> myObjectBuffer;
	ComPtr<ID3D11Buffer> myLightBuffer;
	ComPtr<ID3D11Buffer> myReflectionBuffer;
	ComPtr<ID3D11SamplerState> mySampler;
	ComPtr<ID3D11BlendState> myAdditiveBlendState;
	ComPtr<ID3D11DepthStencilState> myAdditiveDepthState;
	ComPtr<ID3D11RasterizerState> myNoCullRasterizerState;
	ComPtr<ID3D11RasterizerState> myFrontFaceCullingRasterizerState;

	Shader* myLitShader = nullptr;
	Texture myWhiteTexture;
	Texture myFileTexture;

	DirectionalLightConfig myDirectionalLight;
	std::vector<PointLight> myPointLights;
	std::vector<SpotLight> mySpotLights;
	GameObject myPointMarker;
	GameObject mySpotMarker;

	std::vector<GameObject> myObjects;
	std::vector<Mesh> myFbxMeshes;
	Matrix4x4f myFbxTransform;
	GameObject myArenaBlock;
	std::vector<ArenaPiece> myArenaPieces;

	TerrainMesh myTerrain;
	Shader myTerrainShader;
	Texture myGrassColor, myRockColor, mySnowColor;
	Texture myGrassNormal, myRockNormal, mySnowNormal;
	Texture myGrassMaterial, myRockMaterial, mySnowMaterial;
	Cubemap myEnvironmentCubemap;

	RenderTarget myReflectionRT;
	GameObject myWaterObject;
	float myWaterHeight = -5.0f;

	float myTotalTime = 0.0f;
};
