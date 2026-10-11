#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>
#include "GameObject/GameObjectFactory.h"
#include "Graphics/Lights.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/GBuffer.h"
#include "Shader/Shader.h"

#include "CommonUtilities/math/vector3.h"
#include "CommonUtilities/math/Matrix4x4.h"

using Microsoft::WRL::ComPtr;

class Camera;
class Scene;

namespace DeferredShader
{
	enum : int
	{
		ModelGBuffer = 0,
		TerrainGBuffer,
		DirectionalLight,
		LightVolume,
		Tonemap,
		Count
	};
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

struct ReflectionBufferData
{
	float resolution[2];
	float waterHeight;
	float reflectMode;
};

static constexpr int GBUFFER_TEXTURE_SLOT = 14;

class GraphicsRenderer
{
public:
	bool Init();
	void Render(const Scene& aScene, const Camera& aCamera, float aTotalTime);

private:
	bool CreateConstantBuffers();
	bool CreateRenderStates();
	bool CreateShaders();
	bool CreateRenderTargets();

	void UpdateFrameBuffer(const Matrix4x4f& aWorldToClip);
	void UpdateObjectBuffer(const Matrix4x4f& aModelToWorld, const Vector3f& anEmissiveColor = {0, 0, 0},
	                        float anEmissiveStrength = 0.0f);
	void UpdateLightBuffer(const std::vector<LightRef>& someLights, bool anAdditivePass);
	void UpdateReflectionBuffer(float aResolutionX, float aResolutionY, float aWaterHeight, float aReflectMode);
	void BindTerrainTextures(ID3D11DeviceContext* aContext);

	void RenderReflection(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer);
	void RenderGBuffer(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer);
	void RenderDeferredLighting(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer);
	void RenderLightVolumes(ID3D11DeviceContext* aContext);
	void RenderLightMarkers(ID3D11DeviceContext* aContext);
	void RenderWater(ID3D11DeviceContext* aContext);
	void RenderObjectWithLights(ID3D11DeviceContext* aContext, const GameObject& anObject);
	void RenderFullscreen(ID3D11DeviceContext* aContext, const Shader& aShader);

	const Scene* myScene = nullptr;
	const Camera* myCamera = nullptr;
	float myTotalTime = 0.0f;

	ComPtr<ID3D11Buffer> myFrameBuffer;
	ComPtr<ID3D11Buffer> myObjectBuffer;
	ComPtr<ID3D11Buffer> myLightBuffer;
	ComPtr<ID3D11Buffer> myReflectionBuffer;
	ComPtr<ID3D11SamplerState> mySampler;
	ComPtr<ID3D11BlendState> myAdditiveBlendState;
	ComPtr<ID3D11DepthStencilState> myAdditiveDepthState;
	ComPtr<ID3D11DepthStencilState> myReadOnlyGreaterDepthState;
	ComPtr<ID3D11RasterizerState> myNoCullRasterizerState;
	ComPtr<ID3D11RasterizerState> myFrontFaceCullingRasterizerState;

	Shader myTerrainShader;
	Shader myDeferredShaders[DeferredShader::Count];
	GameObject myLightVolume;

	GBuffer myGBuffer;
	RenderTarget mySceneRT;
	RenderTarget myReflectionRT;
};
