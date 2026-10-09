#include "GameWorld.h"
#include "Engine.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <utility>
#include <vector>

#include "AssetPaths.h"
#include "Shader/ShaderFactory.h"
#include "Shader/Shader.h"

#include "TGAFBXImporter/source/Importer.h"

#include "CommonUtilities/input/InputManager.h"
#include "CommonUtilities/TransformUtils.h"
#include "CommonUtilities/Random.h"

GameWorld::~GameWorld()
{
	TGA::FBX::Importer::UninitImporter();
}

bool GameWorld::Init()
{
	TGA::FBX::Importer::InitImporter();
	auto& engine = *Engine::GetInstance();
	auto& ge = engine.GetGraphicsEngine();
	auto device = ge.GetDevice();
	auto context = ge.GetContext();
	assert(device && "device null");
	assert(context && "context null");

	if (!myCamera.Initialize(90.0f, {(float)ge.GetWidth(), (float)ge.GetHeight()}, 0.1f, 1000.0f))
		return false;

	myCamera.SetPosition({0.0f, FLOOR_HEIGHT + 7.0f, -34.0f});
	myCameraController.Initialize(&myCamera, &engine.GetInputManager());

	if (!ShaderFactory::GetInstance().Init(device))
		return false;

	auto& factory = GameObjectFactory::GetInstance();
	if (!factory.Init(device, context))
		return false;

	myLitShader = ShaderFactory::GetInstance().GetShader("lit");

	if (!CreateConstantBuffers())
		return false;

	if (!CreateRenderStates())
		return false;

	myFileTexture = factory.GetTexture("Assets/Textures/texture_2.png", false);

	if (!myTerrainShader.Init(device, "terrain_VS.cso", "terrain_PS.cso", Shader::Layout::Terrain))
		return false;

	const struct
	{
		std::string vertexShader;
		std::string pixelShader;
		Shader::Layout layout;
	}
	deferredShaders[DeferredShader::Count] = {
		{"model_lit_VS.cso", "Model_GBuffer_PS.cso", Shader::Layout::Default},
		{"terrain_VS.cso", "Terrain_GBuffer_PS.cso", Shader::Layout::Terrain},
		{"Fullscreen_VS.cso", "Deferred_Directional_PS.cso", Shader::Layout::None},
		{"default_VS.cso", "Deferred_LightVolume_PS.cso", Shader::Layout::Default},
		{"Fullscreen_VS.cso", "PostprocessTonemapPS.cso", Shader::Layout::None},
	};
	for (int i = 0; i < DeferredShader::Count; ++i)
	{
		const auto& desc = deferredShaders[i];
		if (!myDeferredShaders[i].Init(device, desc.vertexShader, desc.pixelShader, desc.layout))
			return false;
	}

	std::vector<unsigned int> terrainIndices;
	auto terrainVertices = myTerrain.BuildTerrain(terrainIndices);
	if (!myTerrain.Init(device, terrainVertices, terrainIndices))
		return false;

	const std::pair<std::string, bool> terrainTextures[TERRAIN_TEXTURE_COUNT] = {
		{"Grass_c.png", true},
		{"Rock_c.png", true},
		{"Snow_c.png", true},
		{"Grass_n.png", false},
		{"Rock_n.png", false},
		{"Snow_n.png", false},
		{"Grass_m.png", false},
		{"Rock_m.png", false},
		{"Snow_m.png", false},
	};
	for (int i = 0; i < TERRAIN_TEXTURE_COUNT; ++i)
	{
		myTerrainTextures[i] = factory.GetTexture(terrainTextures[i].first, terrainTextures[i].second);
		if (!myTerrainTextures[i])
		{
			assert(false && "GameWorld: failed to load terrain texture");
			return false;
		}
	}

	if (!myEnvironmentCubemap.Initialize(
		device, AssetPaths::ResolveWString(L"cube_1024_preblurred_angle3_Skansen3.dds").c_str()))
		return false;

	const std::pair<std::string, std::string> models[] = {
		{"Chest", "Particle_Chest.fbx"},
		{"StoneFloor", "StoneFloor.fbx"},
		{"StoneFloorBlack", "StoneFloor Low.fbx"},
		{"Jeep", "Jeep_done_2.fbx"},
	};
	for (const auto& [name, path] : models)
	{
		if (!factory.LoadFbx(name, path))
		{
			const std::string message = "LoadFbx failed for '" + name + "' (" + path + "): " +
				TGA::FBX::Importer::GetLastError() + "\n";
			OutputDebugStringA(message.c_str());
			assert(false && "GameWorld: LoadFbx failed, check the path");
			return false;
		}
	}

	if (!myReflectionRT.Initialize(device, ge.GetWidth(), ge.GetHeight()))
		return false;

	if (!myGBuffer.Initialize(device, ge.GetWidth(), ge.GetHeight()))
		return false;

	if (!mySceneRT.Initialize(device, ge.GetWidth(), ge.GetHeight(), DXGI_FORMAT_R16G16B16A16_FLOAT))
		return false;

	CreateObjects();
	CreateLights();

	return true;
}

void GameWorld::Update(float aDeltaTime)
{
	myTotalTime += aDeltaTime;
	myCameraController.Update(aDeltaTime);

	AnimateLights();
}

void GameWorld::Render()
{
	auto& graphicsEngine = Engine::GetInstance()->GetGraphicsEngine();
	auto context = graphicsEngine.GetContext();

	UpdateLightBuffer({}, false);
	UpdateReflectionBuffer((float)graphicsEngine.GetWidth(), (float)graphicsEngine.GetHeight(), myWaterHeight, 1.0f);

	context->RSSetState(myFrontFaceCullingRasterizerState.Get());

	const float reflectionClearColor[4] = {0.45f, 0.6f, 0.75f, 1.0f};
	myReflectionRT.SetAsTarget(context, graphicsEngine.GetDepthBufferDSV());
	myReflectionRT.Clear(context, reflectionClearColor);
	context->ClearDepthStencilView(graphicsEngine.GetDepthBufferDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f,
	                               0);

	Matrix4x4f reflectionMatrix = Matrix4x4f::CreateIdentityMatrix();
	reflectionMatrix(2, 2) = -1.0f;
	reflectionMatrix(4, 2) = 2.0f * myWaterHeight;
	UpdateFrameBuffer(reflectionMatrix * myCamera.GetViewMatrix() * myCamera.GetProjectionMatrix());

	UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
	BindTerrainTextures(context);
	myTerrain.Render({context, &myTerrainShader});

	for (auto& obj : myObjects)
	{
		UpdateObjectBuffer(obj.GetTransform());
		obj.Render(context);
	}

	ID3D11RenderTargetView* backBuffer = graphicsEngine.GetBackBufferRTV();
	ID3D11DepthStencilView* depthBuffer = graphicsEngine.GetDepthBufferDSV();
	ID3D11ShaderResourceView* nullSRV = nullptr;

	context->ClearDepthStencilView(depthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->RSSetState(nullptr);

	UpdateReflectionBuffer((float)graphicsEngine.GetWidth(), (float)graphicsEngine.GetHeight(), myWaterHeight, 0.0f);
	UpdateFrameBuffer(myCamera.GetWorldToClipMatrix());

	RenderGBuffer(context, depthBuffer);
	RenderDeferredLighting(context, depthBuffer);

	context->OMSetRenderTargets(1, &backBuffer, nullptr);
	mySceneRT.BindAsTexture(context, 0);
	RenderFullscreen(context, myDeferredShaders[DeferredShader::Tonemap]);
	context->PSSetShaderResources(0, 1, &nullSRV);

	context->OMSetRenderTargets(1, &backBuffer, depthBuffer);
	context->RSSetState(myNoCullRasterizerState.Get());
	RenderLightMarkers(context);
	context->RSSetState(nullptr);

	UpdateLightBuffer({}, false);
	myReflectionRT.BindAsTexture(context, 11);
	UpdateObjectBuffer(myWaterObject.GetTransform());
	myWaterObject.Render(context);
	context->PSSetShaderResources(11, 1, &nullSRV);
}

bool GameWorld::CreateConstantBuffers()
{
	auto device = Engine::GetInstance()->GetGraphicsEngine().GetDevice();

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	desc.ByteWidth = sizeof(FrameBufferData);
	if (FAILED(device->CreateBuffer(&desc, nullptr, &myFrameBuffer)))
		return false;

	desc.ByteWidth = sizeof(ObjectBufferData);
	if (FAILED(device->CreateBuffer(&desc, nullptr, &myObjectBuffer)))
		return false;

	desc.ByteWidth = sizeof(LightBufferData);
	if (FAILED(device->CreateBuffer(&desc, nullptr, &myLightBuffer)))
		return false;

	desc.ByteWidth = sizeof(ReflectionBufferData);
	if (FAILED(device->CreateBuffer(&desc, nullptr, &myReflectionBuffer)))
		return false;

	return true;
}

bool GameWorld::CreateRenderStates()
{
	auto& ge = Engine::GetInstance()->GetGraphicsEngine();
	auto device = ge.GetDevice();

	D3D11_SAMPLER_DESC sd = {};
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(device->CreateSamplerState(&sd, &mySampler)))
		return false;
	ge.GetContext()->PSSetSamplers(0, 1, mySampler.GetAddressOf());

	D3D11_BLEND_DESC bd = {};
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if (FAILED(device->CreateBlendState(&bd, &myAdditiveBlendState)))
		return false;

	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsd.DepthFunc = D3D11_COMPARISON_GREATER;
	dsd.StencilEnable = false;
	if (FAILED(device->CreateDepthStencilState(&dsd, &myReadOnlyGreaterDepthState)))
		return false;

	D3D11_RASTERIZER_DESC rd = {};
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.DepthClipEnable = true;
	if (FAILED(device->CreateRasterizerState(&rd, &myNoCullRasterizerState)))
		return false;

	rd.CullMode = D3D11_CULL_FRONT;
	if (FAILED(device->CreateRasterizerState(&rd, &myFrontFaceCullingRasterizerState)))
		return false;

	return true;
}

void GameWorld::CreateObjects()
{
	auto& factory = GameObjectFactory::GetInstance();

	constexpr int gridSize = 8;
	constexpr float offset = 3.5f;
	constexpr float offsetMultiplier = 4.f;

	for (int i = 0; i < gridSize; ++i)
	{
		for (int j = 0; j < gridSize; ++j)
		{
			const float posX = ((float)i - offset) * offsetMultiplier;
			const float posZ = ((float)j - offset) * offsetMultiplier;

			GameObject obj;
			switch ((i + j) % 3)
			{
				case 0:
				{
					obj = factory.CreateGameObject("Chest");
					obj.SetScale(0.01f);
					obj.SetPosition({posX, FLOOR_HEIGHT + 0.5f, posZ});
					break;
				}
				case 1:
				{
					obj = factory.CreateGameObject("Cube");
					obj.SetScale(1.5f);
					obj.SetPosition({posX, FLOOR_HEIGHT + 0.75f, posZ});
					break;
				}
				default:
				{
					obj = factory.CreateGameObject("Pyramid");
					obj.SetScale(1.5f);
					obj.SetPosition({posX, FLOOR_HEIGHT, posZ});
					break;
				}
			}
			obj.SetTexture(TextureSlot::Albedo, myFileTexture);
			obj.SetShader(myLitShader);
			myObjects.push_back(obj);
		}
	}

	GameObject stoneFloor = factory.CreateGameObject("StoneFloor");
	stoneFloor.SetShader(myLitShader);
	stoneFloor.SetScale(0.15f);
	stoneFloor.SetPosition({-10.0f, FLOOR_HEIGHT - 1.25f, 5.0f});
	stoneFloor.SetRotation(-90.0f, 0.0f, 0.0f);
	myObjects.push_back(stoneFloor);

	myPointMarker = factory.CreateGameObject("Cube");
	myPointMarker.SetShader(myLitShader);

	mySpotMarker = factory.CreateGameObject("Pyramid");
	mySpotMarker.SetShader(myLitShader);

	myLightVolume = factory.CreateGameObject("Cube");
	myLightVolume.SetShader(&myDeferredShaders[DeferredShader::LightVolume]);

	myWaterObject = factory.CreateGameObject("Plane");
	myWaterObject.SetShader(ShaderFactory::GetInstance().GetShader("water"));
	myWaterObject.SetScale(100.0f);
	myWaterObject.SetPosition({0.0f, myWaterHeight, 0.0f});
}

void GameWorld::CreateLights()
{
	const int pointCount = 100;
	const int spotCount = 30;

	for (int i = 0; i < pointCount; ++i)
	{
		PointLight l;
		l.color = {1.0f, globalRNG.RangeFloat(0.35f, 0.85f), 0.15f};
		l.intensity = 5.0f;
		l.range = 8.0f;
		l.orbitCenter = {0.0f, FLOOR_HEIGHT + globalRNG.RangeFloat(2.0f, 5.0f), 0.0f};
		l.orbitRadius = globalRNG.RangeFloat(3.0f, 17.0f);
		l.orbitSpeed = globalRNG.RangeFloat(0.25f, 0.45f);
		l.phase = globalRNG.RangeFloat(0.0f, FMath::Tau);
		myPointLights.push_back(l);
	}

	for (int i = 0; i < spotCount; ++i)
	{
		SpotLight l;
		l.color = {0.2f, globalRNG.RangeFloat(0.5f, 0.9f), 1.0f};
		l.intensity = 100.0f;
		l.range = 25.0f;
		l.innerAngle = 0.18f;
		l.outerAngle = 0.28f;
		l.orbitRadius = globalRNG.RangeFloat(-5.0f, 17.0f);
		l.orbitSpeed = -globalRNG.RangeFloat(0.15f, 0.65f);
		l.phase = globalRNG.RangeFloat(0.0f, FMath::Tau);
		mySpotLights.push_back(l);
	}
}

void GameWorld::AnimateLights()
{
	for (auto& point : myPointLights)
	{
		float a = myTotalTime * point.orbitSpeed + point.phase;
		point.position = {
			point.orbitCenter.x + cosf(a) * point.orbitRadius,
			point.orbitCenter.y + sinf(a * 0.5f),
			point.orbitCenter.z + sinf(a) * point.orbitRadius
		};
	}

	for (auto& spot : mySpotLights)
	{
		float a = myTotalTime * spot.orbitSpeed + spot.phase;
		spot.position = {
			spot.orbitCenter.x + cosf(a) * spot.orbitRadius,
			FLOOR_HEIGHT + 12.0f,
			spot.orbitCenter.z + sinf(a) * spot.orbitRadius
		};
		spot.direction = {-spot.position.x * 0.15f, -1.0f, -spot.position.z * 0.15f};
	}
}

void GameWorld::UpdateFrameBuffer(const Matrix4x4f& aWorldToClip)
{
	FrameBufferData data = {};
	data.worldToClipMatrix = Matrix4x4f::Transpose(aWorldToClip);
	data.totalTime = myTotalTime;
	data.cameraPosition = myCamera.GetPosition();

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myFrameBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(FrameBufferData));
	context->Unmap(myFrameBuffer.Get(), 0);

	context->VSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());
}

void GameWorld::UpdateObjectBuffer(const Matrix4x4f& aModelToWorld, const Vector3f& anEmissiveColor,
                                   float anEmissiveStrength)
{
	ObjectBufferData data = {};
	data.modelToWorldMatrix = Matrix4x4f::Transpose(aModelToWorld);
	data.emissiveColor = anEmissiveColor;
	data.emissiveStrength = anEmissiveStrength;

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myObjectBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(ObjectBufferData));
	context->Unmap(myObjectBuffer.Get(), 0);

	context->VSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
	context->PSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
}

void GameWorld::UpdateLightBuffer(const std::vector<LightRef>& someLights, bool anAdditivePass)
{
	LightBufferData data = {};
	data.dirLightDirection = myDirectionalLight.direction.GetNormalized();
	data.dirLightColor = myDirectionalLight.color;
	data.dirLightIntensity = myDirectionalLight.intensity;
	data.ambientSky = myDirectionalLight.ambientSky;
	data.ambientGround = myDirectionalLight.ambientGround;
	data.numEnvMapMipLevels = myEnvironmentCubemap.GetNumMips();
	data.cameraPosition = myCamera.GetPosition();
	data.isAdditivePass = anAdditivePass ? 1 : 0;
	data.ambientIntensity = myDirectionalLight.ambientIntensity;

	for (const LightRef& ref : someLights)
	{
		if (ref.isSpot)
		{
			const SpotLight& spot = mySpotLights[ref.index];
			data.spotLights[data.numSpotLights++] = {
				spot.position, spot.range, spot.direction.GetNormalized(), cosf(spot.outerAngle),
				spot.color, spot.intensity, cosf(spot.innerAngle)
			};
		}
		else
		{
			const PointLight& point = myPointLights[ref.index];
			data.pointLights[data.numPointLights++] = {point.position, point.range, point.color, point.intensity};
		}
	}

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myLightBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(LightBufferData));
	context->Unmap(myLightBuffer.Get(), 0);

	context->VSSetConstantBuffers(2, 1, myLightBuffer.GetAddressOf());
	context->PSSetConstantBuffers(2, 1, myLightBuffer.GetAddressOf());
}

void GameWorld::UpdateReflectionBuffer(float aResolutionX, float aResolutionY, float aWaterHeight, float aReflectMode)
{
	ReflectionBufferData data = {};
	data.resolution[0] = aResolutionX;
	data.resolution[1] = aResolutionY;
	data.waterHeight = aWaterHeight;
	data.reflectMode = aReflectMode;

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myReflectionBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(ReflectionBufferData));
	context->Unmap(myReflectionBuffer.Get(), 0);

	context->VSSetConstantBuffers(3, 1, myReflectionBuffer.GetAddressOf());
	context->PSSetConstantBuffers(3, 1, myReflectionBuffer.GetAddressOf());
}

void GameWorld::BindTerrainTextures(ID3D11DeviceContext* aContext)
{
	myEnvironmentCubemap.Bind(aContext, 0);
	for (int i = 0; i < TERRAIN_TEXTURE_COUNT; ++i)
	{
		myTerrainTextures[i]->Bind(aContext, i + 1);
	}
}

std::vector<LightRef> GameWorld::CollectLightsForObject(const Vector3f& anObjectPosition, float anObjectRadius)
{
	std::vector<LightRef> result;

	for (int i = 0; i < (int)myPointLights.size(); ++i)
	{
		float dist = (myPointLights[i].position - anObjectPosition).Length();
		if (dist < myPointLights[i].range + anObjectRadius)
			result.push_back({false, i, dist});
	}

	for (int i = 0; i < (int)mySpotLights.size(); ++i)
	{
		float dist = (mySpotLights[i].position - anObjectPosition).Length();
		if (dist < mySpotLights[i].range + anObjectRadius)
			result.push_back({true, i, dist});
	}

	std::sort(result.begin(), result.end(),
	          [](const LightRef& a, const LightRef& b) { return a.distance < b.distance; });

	return result;
}

void GameWorld::RenderObjectWithLights(ID3D11DeviceContext* aContext, const GameObject& anObject)
{
	const Matrix4x4f& transform = anObject.GetTransform();
	const std::vector<LightRef> lights = CollectLightsForObject(transform.GetPosition(), anObject.GetRadius());
	UpdateObjectBuffer(transform);

	size_t start = 0;
	while (start == 0 || start < lights.size())
	{
		const size_t end = std::min(start + MAX_LIGHTS_PER_PASS, lights.size());
		const std::vector<LightRef> chunk(lights.begin() + start, lights.begin() + end);
		const bool additive = start > 0;

		if (additive)
		{
			const float blendFactor[4] = {};
			aContext->OMSetBlendState(myAdditiveBlendState.Get(), blendFactor, 0xFFFFFFFF);
			aContext->OMSetDepthStencilState(myAdditiveDepthState.Get(), 0);
		}

		UpdateLightBuffer(chunk, additive);
		anObject.Render(aContext);

		if (end == start)
			break;
		start = end;
	}

	aContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	aContext->OMSetDepthStencilState(nullptr, 0);
}

void GameWorld::RenderLightMarkers(ID3D11DeviceContext* aContext)
{
	UpdateLightBuffer({}, false);

	for (const auto& l : myPointLights)
	{
		UpdateObjectBuffer(BuildBoxTransform(l.position, {0.8f, 0.8f, 0.8f}), l.color, 1.0f);
		myPointMarker.Render(aContext);
	}

	for (const auto& l : mySpotLights)
	{
		UpdateObjectBuffer(BuildAimedTransform(l.position, l.direction, 1.5f), l.color, 1.5f);
		mySpotMarker.Render(aContext);
	}
}

void GameWorld::RenderGBuffer(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer)
{
	myGBuffer.Clear(aContext);
	myGBuffer.SetAsTarget(aContext, aDepthBuffer);

	UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
	BindTerrainTextures(aContext);
	myTerrain.Render({aContext, &myDeferredShaders[DeferredShader::TerrainGBuffer]});

	aContext->RSSetState(myNoCullRasterizerState.Get());

	for (const auto& obj : myObjects)
	{
		UpdateObjectBuffer(obj.GetTransform());
		obj.Render(aContext, &myDeferredShaders[DeferredShader::ModelGBuffer]);
	}

	aContext->RSSetState(nullptr);
}

void GameWorld::RenderDeferredLighting(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer)
{
	const float sceneClearColor[4] = {0.1f, 0.1f, 0.15f, 1.0f};
	mySceneRT.SetAsTarget(aContext, nullptr);
	mySceneRT.Clear(aContext, sceneClearColor);

	myGBuffer.BindAsTextures(aContext, GBUFFER_TEXTURE_SLOT);
	myEnvironmentCubemap.Bind(aContext, 0);

	UpdateLightBuffer({}, false);
	RenderFullscreen(aContext, myDeferredShaders[DeferredShader::DirectionalLight]);

	const float blendFactor[4] = {};
	mySceneRT.SetAsTarget(aContext, aDepthBuffer);
	aContext->OMSetBlendState(myAdditiveBlendState.Get(), blendFactor, 0xFFFFFFFF);
	aContext->OMSetDepthStencilState(myReadOnlyGreaterDepthState.Get(), 0);
	aContext->RSSetState(myFrontFaceCullingRasterizerState.Get());

	RenderLightVolumes(aContext);

	aContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	aContext->OMSetDepthStencilState(nullptr, 0);
	aContext->RSSetState(nullptr);

	myGBuffer.UnbindTextures(aContext, GBUFFER_TEXTURE_SLOT);
}

void GameWorld::RenderLightVolumes(ID3D11DeviceContext* aContext)
{
	for (int i = 0; i < (int)myPointLights.size(); ++i)
	{
		const float size = myPointLights[i].range * 2.0f;
		UpdateLightBuffer({LightRef{false, i, 0.0f}}, true);
		UpdateObjectBuffer(BuildBoxTransform(myPointLights[i].position, {size, size, size}));
		myLightVolume.Render(aContext);
	}

	for (int i = 0; i < (int)mySpotLights.size(); ++i)
	{
		const float size = mySpotLights[i].range * 2.0f;
		UpdateLightBuffer({LightRef{true, i, 0.0f}}, true);
		UpdateObjectBuffer(BuildBoxTransform(mySpotLights[i].position, {size, size, size}));
		myLightVolume.Render(aContext);
	}
}

void GameWorld::RenderFullscreen(ID3D11DeviceContext* aContext, const Shader& aShader)
{
	aContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	aContext->IASetInputLayout(nullptr);
	aContext->VSSetShader(aShader.GetVertexShader(), nullptr, 0);
	aContext->PSSetShader(aShader.GetPixelShader(), nullptr, 0);
	aContext->Draw(3, 0);
}
