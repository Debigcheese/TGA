#include "GameWorld.h"
#include "Engine.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <utility>
#include <vector>
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

	std::vector<unsigned int> terrainIndices;
	auto terrainVertices = myTerrain.BuildTerrain(terrainIndices);
	if (!myTerrain.Init(device, terrainVertices, terrainIndices))
		return false;

	const std::pair<const char*, bool> terrainTextures[TERRAIN_TEXTURE_COUNT] = {
		{"Assets/Textures/Grass_c.png", true},
		{"Assets/Textures/Rock_c.png", true},
		{"Assets/Textures/Snow_c.png", true},
		{"Assets/Textures/Grass_n.png", false},
		{"Assets/Textures/Rock_n.png", false},
		{"Assets/Textures/Snow_n.png", false},
		{"Assets/Textures/cubemap/Grass_m.png", false},
		{"Assets/Textures/cubemap/Rock_m.png", false},
		{"Assets/Textures/cubemap/Snow_m.png", false},
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

	if (!myEnvironmentCubemap.Initialize(device, L"Assets/Textures/cubemap/cube_1024_preblurred_angle3_Skansen3.dds"))
		return false;

	const std::pair<const char*, const char*> models[] = {
		{"Chest", "../../Assets/Models/Particle_Chest.fbx"},
		{"StoneFloor", "../../Assets/Models/stone-floor/source/StoneFloor.fbx"},
		{"StoneFloorBlack", "../../Assets/Models/stone-floor-black/source/StoneFloor Low.fbx"},
		{"Jeep", "../../Assets/Models/Jeep_done_2.fbx"},
	};
	for (const auto& [name, path] : models)
	{
		if (!factory.LoadFbx(name, path))
		{
			assert(false && "GameWorld: LoadFbx failed, check the path");
			return false;
		}
	}

	if (!myReflectionRT.Initialize(device, ge.GetWidth(), ge.GetHeight()))
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
	context->OMSetRenderTargets(1, &backBuffer, graphicsEngine.GetDepthBufferDSV());
	context->ClearDepthStencilView(graphicsEngine.GetDepthBufferDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f,
	                               0);
	context->RSSetState(nullptr);

	UpdateReflectionBuffer((float)graphicsEngine.GetWidth(), (float)graphicsEngine.GetHeight(), myWaterHeight, 0.0f);
	UpdateFrameBuffer(myCamera.GetWorldToClipMatrix());

	UpdateLightBuffer({}, false);
	UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
	BindTerrainTextures(context);
	myTerrain.Render({context, &myTerrainShader});

	context->RSSetState(myNoCullRasterizerState.Get());

	for (const auto& obj : myObjects)
	{
		RenderObjectWithLights(context, obj);
	}

	RenderLightMarkers(context);

	context->RSSetState(nullptr);

	UpdateLightBuffer({}, false);
	myReflectionRT.BindAsTexture(context, 11);

	UpdateObjectBuffer(myWaterObject.GetTransform());
	myWaterObject.Render(context);

	ID3D11ShaderResourceView* nullSRV = nullptr;
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
	dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dsd.StencilEnable = false;
	if (FAILED(device->CreateDepthStencilState(&dsd, &myAdditiveDepthState)))
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

	for (int x = 0; x < gridSize; ++x)
	{
		for (int z = 0; z < gridSize; ++z)
		{
			const float posX = ((float)x - offset) * offsetMultiplier;
			const float posZ = ((float)z - offset) * offsetMultiplier;

			GameObject obj;
			switch ((x + z) % 3)
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
	stoneFloor.SetScale(0.10f);
	stoneFloor.SetPosition({0.0f, FLOOR_HEIGHT + 0.05f, 0.0f});
	stoneFloor.SetRotation(-90.0f, 0.0f, 0.0f);
	myObjects.push_back(stoneFloor);

	myPointMarker = factory.CreateGameObject("Cube");
	myPointMarker.SetShader(myLitShader);

	mySpotMarker = factory.CreateGameObject("Pyramid");
	mySpotMarker.SetShader(myLitShader);

	myWaterObject = factory.CreateGameObject("Plane");
	myWaterObject.SetShader(ShaderFactory::GetInstance().GetShader("water"));
	myWaterObject.SetScale(100.0f);
	myWaterObject.SetPosition({0.0f, myWaterHeight, 0.0f});
}

void GameWorld::CreateLights()
{
	const int pointCount = 30;
	const int spotCount = 20;

	for (int i = 0; i < pointCount; ++i)
	{
		PointLight l;
		l.color = {1.0f, globalRNG.RangeFloat(0.35f, 0.85f), 0.15f};
		l.intensity = 1.5f;
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
		l.intensity = 2.5f;
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
	for (auto& l : myPointLights)
	{
		float a = myTotalTime * l.orbitSpeed + l.phase;
		l.position = {
			l.orbitCenter.x + cosf(a) * l.orbitRadius,
			l.orbitCenter.y + sinf(a * 0.5f),
			l.orbitCenter.z + sinf(a) * l.orbitRadius
		};
	}

	for (auto& l : mySpotLights)
	{
		float a = myTotalTime * l.orbitSpeed + l.phase;
		l.position = {
			l.orbitCenter.x + cosf(a) * l.orbitRadius,
			FLOOR_HEIGHT + 12.0f,
			l.orbitCenter.z + sinf(a) * l.orbitRadius
		};
		l.direction = {-l.position.x * 0.15f, -1.0f, -l.position.z * 0.15f};
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

	for (const LightRef& ref : someLights)
	{
		if (ref.isSpot)
		{
			const SpotLight& l = mySpotLights[ref.index];
			data.spotLights[data.numSpotLights++] = {
				l.position, l.range, l.direction.GetNormalized(), cosf(l.outerAngle),
				l.color, l.intensity, cosf(l.innerAngle)
			};
		}
		else
		{
			const PointLight& l = myPointLights[ref.index];
			data.pointLights[data.numPointLights++] = {l.position, l.range, l.color, l.intensity};
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
	std::vector<LightRef> lights = CollectLightsForObject(transform.GetPosition(), anObject.GetRadius());

	int lightsDone = 0;
	bool firstPass = true;

	do
	{
		std::vector<LightRef> chunk;
		for (int i = lightsDone; i < (int)lights.size() && (int)chunk.size() < MAX_LIGHTS_PER_PASS; ++i)
		{
			chunk.push_back(lights[i]);
		}
		lightsDone += (int)chunk.size();

		UpdateLightBuffer(chunk, !firstPass);
		UpdateObjectBuffer(transform);

		if (!firstPass)
		{
			const float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
			aContext->OMSetBlendState(myAdditiveBlendState.Get(), blendFactor, 0xFFFFFFFF);
			aContext->OMSetDepthStencilState(myAdditiveDepthState.Get(), 0);
		}

		anObject.Render(aContext);
		firstPass = false;
	}
	while (lightsDone < (int)lights.size());

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
