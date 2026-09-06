#include "GameWorld.h"
#include "Engine.h"
#include <cassert>
#include <cstring>
#include <cmath>
#include <vector>
#include "Shader/ShaderFactory.h"
#include "Shader/Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "TGAFBXImporter/source/Importer.h"
#include "Model/FBXLoader.h"

#include "CommonUtilities/input/InputManager.h"
#include "CommonUtilities/TransformUtils.h"

static constexpr float kObjectRadius = 2.0f;
static constexpr float kArenaFloorY = 30.0f;

GameWorld::~GameWorld()
{
	TGA::FBX::Importer::UninitImporter();
}

bool GameWorld::Init()
{
	TGA::FBX::Importer::InitImporter();
	auto& engine = *Engine::GetInstance();
	auto device = engine.GetGraphicsEngine().GetDevice();
	auto context = engine.GetGraphicsEngine().GetContext();
	assert(device && "device null");
	assert(context && "context null");
	if (!myCamera.Initialize(90.0f, {
								 (float)engine.GetGraphicsEngine().GetWidth(),
								 (float)engine.GetGraphicsEngine().GetHeight()
		}, 0.1f, 1000.0f))
		return false;

	myCamera.SetPosition({ 0.0f, kArenaFloorY + 7.0f, -34.0f });
	myCameraController.Initialize(&myCamera, &engine.GetInputManager());

	auto& shaderFactory = ShaderFactory::GetInstance();
	if (!shaderFactory.Init(device))
		return false;

	auto& objectFactory = GameObjectFactory::GetInstance();
	if (!objectFactory.Init(device))
		return false;

	{
		D3D11_SAMPLER_DESC sd = {};
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.MaxLOD = D3D11_FLOAT32_MAX;
		if (FAILED(device->CreateSamplerState(&sd, &mySampler))) return false;
		context->PSSetSamplers(0, 1, mySampler.GetAddressOf());
	}

	if (!myTerrainShader.Init(device, "terrain_VS.cso", "terrain_PS.cso", Shader::Layout::Terrain))
		return false;

	{
		std::vector<unsigned int> idx;
		auto verts = myTerrain.BuildTerrain(idx);
		if (!myTerrain.Init(device, verts, idx)) return false;
	}

	{
		int tw, th, ch;
		unsigned char* img = stbi_load("texture_2.png", &tw, &th, &ch, 0);

		if (img && (ch == 3 || ch == 4))
		{
			if (ch == 3)
			{
				std::vector<unsigned char> rgba(tw * th * 4);
				for (int i = 0; i < tw * th; ++i)
				{
					rgba[4 * i + 0] = img[3 * i + 0];
					rgba[4 * i + 1] = img[3 * i + 1];
					rgba[4 * i + 2] = img[3 * i + 2];
					rgba[4 * i + 3] = 255;
				}
				myFileTexture.Initialize(device, context, rgba.data(), tw, th, false);
			}
			else
			{
				myFileTexture.Initialize(device, context, img, tw, th, false);
			}
			stbi_image_free(img);
		}
		else
		{
			if (img) stbi_image_free(img);
			// Fallback: solid purple 2x2
			unsigned char fallback[] = { 180, 80, 220, 255, 80, 180, 220, 255, 80, 180, 220, 255, 180, 80, 220, 255 };
			myFileTexture.Initialize(device, context, fallback, 2, 2, false);
		}
	}
	{
		unsigned char white[] = { 255, 255, 255, 255 };
		myWhiteTexture.Initialize(device, context, white, 1, 1, false);
	}
	Mesh::SetFallbackTexture(&myWhiteTexture);

	LoadTextureFromFile(device, context, "Assets/Textures/Grass_c.png", myGrassColor, true);
	LoadTextureFromFile(device, context, "Assets/Textures/Grass_n.png", myGrassNormal, false);
	LoadTextureFromFile(device, context, "Assets/Textures/Rock_c.png", myRockColor, true);
	LoadTextureFromFile(device, context, "Assets/Textures/Rock_n.png", myRockNormal, false);
	LoadTextureFromFile(device, context, "Assets/Textures/Snow_c.png", mySnowColor, true);
	LoadTextureFromFile(device, context, "Assets/Textures/Snow_n.png", mySnowNormal, false);

	LoadTextureFromFile(device, context, "Assets/Textures/cubemap/Grass_m.png", myGrassMaterial, false);
	LoadTextureFromFile(device, context, "Assets/Textures/cubemap/Rock_m.png", myRockMaterial, false);
	LoadTextureFromFile(device, context, "Assets/Textures/cubemap/Snow_m.png", mySnowMaterial, false);

	if (!myEnvironmentCubemap.Initialize(device, L"Assets/Textures/cubemap/cube_1024_preblurred_angle3_Skansen3.dds"))
		return false;

	{
		D3D11_RASTERIZER_DESC rastDesc = {};
		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.CullMode = D3D11_CULL_FRONT;
		rastDesc.FrontCounterClockwise = false;

		HRESULT hr = device->CreateRasterizerState(&rastDesc, &myFrontFaceCullingRasterizerState);
		if (FAILED(hr)) return false;
	}

	if (!LoadFBXModel(device, "../../Assets/Models/low-poly-truck-car-drifter/Particle_Chest.fbx", myFbxMeshes))
	{
		assert(false && "GameWorld: LoadFBXModel failed to load fbx");
		return false;
	}

	myFbxTransform = BuildBoxTransform(
		{ 0.0f, kArenaFloorY + 2.0f, 0.0f },
		{ 0.01f, 0.01f, 0.01f });

	Shader* litShader = ShaderFactory::GetInstance().GetShader("lit");

	const int gridSize = 8;
	for (int x = 0; x < gridSize; ++x)
	{
		for (int z = 0; z < gridSize; ++z)
		{
			int i = x * gridSize + z;
			bool useCube = (i % 2 == 0);

			auto obj = objectFactory.CreateGameObject(useCube ? "Cube" : "Pyramid");
			obj.SetPosition({
				((float)x - 3.5f) * 4.0f,
				kArenaFloorY + 0.5f,
				((float)z - 3.5f) * 4.0f
				});
			obj.SetTexture(useCube ? &myWhiteTexture : &myFileTexture);
			obj.SetShader(litShader);
			obj.SetMesh(&myFbxMeshes[0]);
			obj.SetScale(0.01f);

			myObjects.push_back(obj);
		}
	}

	auto& ge = engine.GetGraphicsEngine();
	if (!myReflectionRT.Initialize(device, ge.GetWidth(), ge.GetHeight()))
		return false;

	myWaterObject = objectFactory.CreateGameObject("Plane");
	myWaterObject.SetShader(ShaderFactory::GetInstance().GetShader("water"));
	myWaterObject.SetScale(100.0f);
	myWaterObject.SetPosition({ 0.0f, myWaterHeight, 0.0f });

	myArenaBlock = objectFactory.CreateGameObject("Cube");
	myArenaBlock.SetShader(litShader);
	myArenaBlock.SetTexture(&myWhiteTexture);

	myPointMarker = objectFactory.CreateGameObject("Cube");
	myPointMarker.SetShader(litShader);
	myPointMarker.SetTexture(&myWhiteTexture);

	mySpotMarker = objectFactory.CreateGameObject("Pyramid");
	mySpotMarker.SetShader(litShader);
	mySpotMarker.SetTexture(&myWhiteTexture);

	if (!CreateConstantBuffers())
		return false;

	if (!CreateRenderStates())
		return false;

	CreateLights();

	return true;
}

void GameWorld::Render()
{
	auto& engine = *Engine::GetInstance();
	auto& ge = engine.GetGraphicsEngine();
	auto context = ge.GetContext();

	//  PASS 1: Reflektion till render target
	UpdateLightBuffer({}, false);

	UpdateReflectionBuffer((float)ge.GetWidth(), (float)ge.GetHeight(),
		myWaterHeight, 1.0f);

	context->RSSetState(myFrontFaceCullingRasterizerState.Get());

	const float reflClear[4] = { 0.45f, 0.6f, 0.75f, 1.0f };
	myReflectionRT.SetAsTarget(context, ge.GetDepthBufferDSV());
	myReflectionRT.Clear(context, reflClear);
	context->ClearDepthStencilView(ge.GetDepthBufferDSV(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Matrix4x4f view = myCamera.GetViewMatrix();
	Matrix4x4f proj = myCamera.GetProjectionMatrix();

	Matrix4x4f reflectionMatrix = Matrix4x4f::CreateIdentityMatrix();
	reflectionMatrix(2, 2) = -1.0f;
	reflectionMatrix(4, 2) = 2.0f * myWaterHeight;

	Matrix4x4f reflectedView = reflectionMatrix * view;
	Matrix4x4f reflectedViewProj = reflectedView * proj;
	UpdateFrameBuffer(reflectedViewProj);

	UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
	BindTerrainTextures(context);
	myTerrain.Render({ context, &myTerrainShader });

	for (auto& obj : myObjects)
	{
		UpdateObjectBuffer(obj.GetTransform());
		obj.Render(context);
	}

	//  PASS 2: Vanlig scen
	ID3D11RenderTargetView* backRTV = ge.GetBackBufferRTV();
	context->OMSetRenderTargets(1, &backRTV, ge.GetDepthBufferDSV());
	context->ClearDepthStencilView(ge.GetDepthBufferDSV(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	context->RSSetState(nullptr);

	UpdateReflectionBuffer((float)ge.GetWidth(), (float)ge.GetHeight(),
		myWaterHeight, 0.0f);

	UpdateFrameBuffer(myCamera.GetWorldToClipMatrix());

	UpdateLightBuffer({}, false);
	UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
	BindTerrainTextures(context);
	myTerrain.Render({ context, &myTerrainShader });

	context->RSSetState(myNoCullRasterizerState.Get());

	RenderArena(context);

	for (auto& obj : myObjects)
	{
		RenderObjectWithLights(context, obj);
	}
	{
		Shader* litShader = ShaderFactory::GetInstance().GetShader("lit");
		UpdateObjectBuffer(myFbxTransform);
		for (const Mesh& mesh : myFbxMeshes)
		{
			mesh.Render({ context, litShader, &myWhiteTexture });
		}
	}
	RenderLightMarkers(context);

	context->RSSetState(nullptr);

	// PASS 3: Vatten
	UpdateLightBuffer({}, false);
	myReflectionRT.BindAsTexture(context, 11);

	UpdateObjectBuffer(myWaterObject.GetTransform());
	myWaterObject.Render(context);

	ID3D11ShaderResourceView* nullSRV = nullptr;
	context->PSSetShaderResources(10, 1, &nullSRV);
}

bool GameWorld::CreateConstantBuffers()
{
	HRESULT result;

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	auto& engine = *Engine::GetInstance();
	auto device = engine.GetGraphicsEngine().GetDevice();

	desc.ByteWidth = sizeof(FrameBufferData);
	result = device->CreateBuffer(&desc, nullptr, &myFrameBuffer);
	assert(SUCCEEDED(result) && "Failed to create frame constant buffer");
	if (FAILED(result)) return false;

	desc.ByteWidth = sizeof(ObjectBufferData);
	result = device->CreateBuffer(&desc, nullptr, &myObjectBuffer);
	assert(SUCCEEDED(result) && "Failed to create object constant buffer");
	if (FAILED(result)) return false;

	desc.ByteWidth = sizeof(LightBufferData);
	result = device->CreateBuffer(&desc, nullptr, &myLightBuffer);
	assert(SUCCEEDED(result) && "Failed to create light constant buffer");
	if (FAILED(result)) return false;

	desc.ByteWidth = sizeof(ReflectionBufferData);
	result = device->CreateBuffer(&desc, nullptr, &myReflectionBuffer);
	assert(SUCCEEDED(result) && "Failed to create reflection constant buffer");
	if (FAILED(result)) return false;

	return true;
}

bool GameWorld::CreateRenderStates()
{
	auto device = Engine::GetInstance()->GetGraphicsEngine().GetDevice();

	D3D11_BLEND_DESC bd = {};
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if (FAILED(device->CreateBlendState(&bd, &myAdditiveBlendState))) return false;

	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dsd.StencilEnable = false;
	if (FAILED(device->CreateDepthStencilState(&dsd, &myAdditiveDepthState))) return false;
	D3D11_RASTERIZER_DESC rd = {};

	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable = true;
	if (FAILED(device->CreateRasterizerState(&rd, &myNoCullRasterizerState))) return false;

	return true;
}

void GameWorld::CreateLights()
{
	const int pointCount = 8;
	const int spotCount = 5;

	for (int i = 0; i < pointCount; ++i)
	{
		PointLight l;
		float t = (float)i / (float)pointCount;

		l.color = { 1.0f, 0.35f + 0.5f * t, 0.15f };
		l.intensity = 2.5f;
		l.range = 10.0f;

		l.orbitCenter = { 0.0f, kArenaFloorY + 2.5f + (float)(i % 3) * 1.5f, 0.0f };
		l.orbitRadius = 5.0f + (float)(i % 5) * 3.0f;
		l.orbitSpeed = 0.25f + 0.04f * (float)(i % 6);
		l.phase = t * 6.283f;

		myPointLights.push_back(l);
	}

	for (int i = 0; i < spotCount; ++i)
	{
		SpotLight l;
		float t = (float)i / (float)spotCount;

		l.color = { 0.2f, 0.5f + 0.4f * t, 1.0f };
		l.intensity = 4.0f;
		l.range = 25.0f;
		l.innerAngle = 0.18f;
		l.outerAngle = 0.28f;

		l.orbitCenter = { 0.0f, 0.0f, 0.0f };
		l.orbitRadius = 5.0f + (float)(i % 5) * 3.0f;
		l.orbitSpeed = -0.15f - 0.025f * (float)(i % 5);
		l.phase = t * 6.283f;

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
			l.orbitCenter.y + sinf(a * 0.5f) * 1.0f,
			l.orbitCenter.z + sinf(a) * l.orbitRadius
		};
	}

	for (auto& l : mySpotLights)
	{
		float a = myTotalTime * l.orbitSpeed + l.phase;
		l.position = {
			l.orbitCenter.x + cosf(a) * l.orbitRadius,
			kArenaFloorY + 12.0f,
			l.orbitCenter.z + sinf(a) * l.orbitRadius
		};

		l.direction = { -l.position.x * 0.15f, -1.0f, -l.position.z * 0.15f };
	}
}

std::vector<LightRef> GameWorld::CollectLightsForObject(const Vector3f& anObjectPosition, float anObjectRadius)
{
	std::vector<LightRef> result;

	for (int i = 0; i < (int)myPointLights.size(); ++i)
	{
		float dist = (myPointLights[i].position - anObjectPosition).Length();
		if (dist < myPointLights[i].range + anObjectRadius)
			result.push_back({ false, i, dist });
	}

	for (int i = 0; i < (int)mySpotLights.size(); ++i)
	{
		float dist = (mySpotLights[i].position - anObjectPosition).Length();
		if (dist < mySpotLights[i].range + anObjectRadius)
			result.push_back({ true, i, dist });
	}

	std::sort(result.begin(), result.end(),
		[](const LightRef& a, const LightRef& b) { return a.distance < b.distance; });

	return result;
}

void GameWorld::RenderPieceWithLights(ID3D11DeviceContext* aContext,
	GameObject& anObject,
	const Matrix4x4f& aTransform,
	const Vector3f& aWorldPosition,
	float aRadius)
{
	std::vector<LightRef> lights = CollectLightsForObject(aWorldPosition, aRadius);

	int lightsDone = 0;
	bool firstPass = true;

	do
	{
		std::vector<LightRef> chunk;
		for (int i = lightsDone;
			i < (int)lights.size() && (int)chunk.size() < MAX_LIGHTS_PER_PASS;
			++i)
		{
			chunk.push_back(lights[i]);
		}
		lightsDone += (int)chunk.size();

		UpdateLightBuffer(chunk, !firstPass);
		UpdateObjectBuffer(aTransform);

		if (!firstPass)
		{
			const float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			aContext->OMSetBlendState(myAdditiveBlendState.Get(), blendFactor, 0xFFFFFFFF);
			aContext->OMSetDepthStencilState(myAdditiveDepthState.Get(), 0);
		}

		anObject.Render(aContext);
		firstPass = false;
	} while (lightsDone < (int)lights.size());

	aContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	aContext->OMSetDepthStencilState(nullptr, 0);
}

void GameWorld::RenderArena(ID3D11DeviceContext* aContext)
{
	const float half = 20.0f;
	const int tiles = 4;
	const float tileSize = (half * 2.0f) / tiles;
	const float wallH = 8.0f;

	for (int x = 0; x < tiles; ++x)
	{
		for (int z = 0; z < tiles; ++z)
		{
			Vector3f pos = {
				-half + tileSize * ((float)x + 0.5f),
				kArenaFloorY - 0.5f,
				-half + tileSize * ((float)z + 0.5f)
			};

			Matrix4x4f m = BuildBoxTransform(pos, { tileSize, 1.0f, tileSize });
			RenderPieceWithLights(aContext, myArenaBlock, m, pos, tileSize * 0.75f);
		}
	}

	struct Wall
	{
		Vector3f pos;
		Vector3f scale;
	};
	const Wall walls[3] =
	{
		{{0.0f, kArenaFloorY + wallH * 0.5f, half}, {half * 2.0f, wallH, 1.0f}},
		{{-half, kArenaFloorY + wallH * 0.5f, 0.0f}, {1.0f, wallH, half * 2.0f}},
		{{half, kArenaFloorY + wallH * 0.5f, 0.0f}, {1.0f, wallH, half * 2.0f}},
	};

	for (const Wall& w : walls)
	{
		Matrix4x4f m = BuildBoxTransform(w.pos, w.scale);
		RenderPieceWithLights(aContext, myArenaBlock, m, w.pos, half);
	}
}

void GameWorld::RenderObjectWithLights(ID3D11DeviceContext* aContext, GameObject& anObject)
{
	Matrix4x4f t = anObject.GetTransform();
	RenderPieceWithLights(aContext, anObject, t, t.GetPosition(), kObjectRadius);
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

void GameWorld::UpdateReflectionBuffer(float resX, float resY,
	float waterH, float mode)
{
	auto& ge = Engine::GetInstance()->GetGraphicsEngine();
	auto context = ge.GetContext();

	ReflectionBufferData data = {};
	data.resolution[0] = resX;
	data.resolution[1] = resY;
	data.waterHeight = waterH;
	data.reflectMode = mode;

	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myReflectionBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(ReflectionBufferData));
	context->Unmap(myReflectionBuffer.Get(), 0);

	context->VSSetConstantBuffers(3, 1, myReflectionBuffer.GetAddressOf());
	context->PSSetConstantBuffers(3, 1, myReflectionBuffer.GetAddressOf());
}

void GameWorld::BindTerrainTextures(ID3D11DeviceContext* context)
{
	myEnvironmentCubemap.Bind(context, 0);
	myGrassColor.Bind(context, 1);
	myRockColor.Bind(context, 2);
	mySnowColor.Bind(context, 3);
	myGrassNormal.Bind(context, 4);
	myRockNormal.Bind(context, 5);
	mySnowNormal.Bind(context, 6);
	myGrassMaterial.Bind(context, 7);
	myRockMaterial.Bind(context, 8);
	mySnowMaterial.Bind(context, 9);
}

void GameWorld::UpdateObjectBuffer(const Matrix4x4f& aModelToWorld,
	const Vector3f& anEmissiveColor,
	float anEmissiveStrength)
{
	ObjectBufferData data = {};
	data.modelToWorldMatrix = Matrix4x4f::Transpose(aModelToWorld);
	data.emissiveColor[0] = anEmissiveColor.x;
	data.emissiveColor[1] = anEmissiveColor.y;
	data.emissiveColor[2] = anEmissiveColor.z;
	data.emissiveStrength = anEmissiveStrength;

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();

	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myObjectBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(ObjectBufferData));
	context->Unmap(myObjectBuffer.Get(), 0);

	context->VSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
	context->PSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
}

void GameWorld::RenderLightMarkers(ID3D11DeviceContext* aContext)
{
	UpdateLightBuffer({}, false);

	for (const auto& l : myPointLights)
	{
		Matrix4x4f m = BuildBoxTransform(l.position, { 0.8f, 0.8f, 0.8f });
		UpdateObjectBuffer(m, l.color, 1.0f);
		myPointMarker.Render(aContext);
	}

	for (const auto& l : mySpotLights)
	{
		Matrix4x4f body = BuildAimedTransform(l.position, l.direction, 1.5f);
		UpdateObjectBuffer(body, l.color, 1.5f);
		mySpotMarker.Render(aContext);
	}
}

void GameWorld::UpdateLightBuffer(const std::vector<LightRef>& someLights, bool anAdditivePass)
{
	auto& c = myLightConfig;

	float sunY = cosf(myDayAngle);

	float shifted = sunY + c.dayShift;
	float day = FMath::Saturate(shifted / c.dayRange);
	day = day * day * (3.0f - 2.0f * day);

	Vector3f sunDir = Vector3f(sinf(myDayAngle), cosf(myDayAngle), c.sunDirZ).GetNormalized();

	LightBufferData data = {};

	data.dirLightDir[0] = sunDir.x;
	data.dirLightDir[1] = sunDir.y;
	data.dirLightDir[2] = sunDir.z;

	float str = FMath::Lerp(c.dirStrengthMin, c.dirStrengthMax, day);
	str *= 0.08f;
	data.dirLightColor[0] = c.dirColorR;
	data.dirLightColor[1] = c.dirColorG;
	data.dirLightColor[2] = c.dirColorB;
	data.dirLightIntensity = str;

	data.ambientColor[0] = 1.0f;
	data.ambientColor[1] = 1.0f;
	data.ambientColor[2] = 1.0f;
	data.ambientIntensity = 1.0f;

	data.ambientGround[0] = FMath::Lerp(c.ambGndMinR, c.ambGndMaxR, day);
	data.ambientGround[1] = FMath::Lerp(c.ambGndMinG, c.ambGndMaxG, day);
	data.ambientGround[2] = FMath::Lerp(c.ambGndMinB, c.ambGndMaxB, day);

	data.ambientSky[0] = FMath::Lerp(c.ambSkyMinR, c.ambSkyMaxR, day);
	data.ambientSky[1] = FMath::Lerp(c.ambSkyMinG, c.ambSkyMaxG, day);
	data.ambientSky[2] = FMath::Lerp(c.ambSkyMinB, c.ambSkyMaxB, day);

	for (int i = 0; i < 3; ++i)
	{
		data.ambientGround[i] *= 0.15f;
		data.ambientSky[i] *= 0.15f;
	}

	data.numEnvMapMipLevels = myEnvironmentCubemap.GetNumMips();

	data.cameraPosition[0] = myCamera.GetPosition().x;
	data.cameraPosition[1] = myCamera.GetPosition().y;
	data.cameraPosition[2] = myCamera.GetPosition().z;

	data.isAdditivePass = anAdditivePass ? 1 : 0;

	int p = 0;
	int s = 0;

	for (const LightRef& ref : someLights)
	{
		if (!ref.isSpot)
		{
			const PointLight& l = myPointLights[ref.index];
			data.pointLights[p].position[0] = l.position.x;
			data.pointLights[p].position[1] = l.position.y;
			data.pointLights[p].position[2] = l.position.z;
			data.pointLights[p].range = l.range;
			data.pointLights[p].color[0] = l.color.x;
			data.pointLights[p].color[1] = l.color.y;
			data.pointLights[p].color[2] = l.color.z;
			data.pointLights[p].intensity = l.intensity;
			++p;
		}
		else
		{
			const SpotLight& l = mySpotLights[ref.index];
			Vector3f dir = l.direction.GetNormalized();

			data.spotLights[s].position[0] = l.position.x;
			data.spotLights[s].position[1] = l.position.y;
			data.spotLights[s].position[2] = l.position.z;
			data.spotLights[s].range = l.range;
			data.spotLights[s].direction[0] = dir.x;
			data.spotLights[s].direction[1] = dir.y;
			data.spotLights[s].direction[2] = dir.z;
			data.spotLights[s].cosOuter = cosf(l.outerAngle);
			data.spotLights[s].color[0] = l.color.x;
			data.spotLights[s].color[1] = l.color.y;
			data.spotLights[s].color[2] = l.color.z;
			data.spotLights[s].intensity = l.intensity;
			data.spotLights[s].cosInner = cosf(l.innerAngle);
			++s;
		}
	}

	data.numPointLights = p;
	data.numSpotLights = s;

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();

	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myLightBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(LightBufferData));
	context->Unmap(myLightBuffer.Get(), 0);

	context->VSSetConstantBuffers(2, 1, myLightBuffer.GetAddressOf());
	context->PSSetConstantBuffers(2, 1, myLightBuffer.GetAddressOf());
}

bool GameWorld::LoadTextureFromFile(ID3D11Device* device, ID3D11DeviceContext* context,
	const char* path, Texture& tex, bool srgb)
{
	int w, h, ch;
	unsigned char* img = stbi_load(path, &w, &h, &ch, 4);
	if (!img)
	{
		assert(false && "LoadTextureFromFile: failed to load file");
		return false;
	}
	bool ok = tex.Initialize(device, context, img, w, h, srgb);
	stbi_image_free(img);
	return ok;
}

void GameWorld::Update(float aDeltaTime)
{
	myTotalTime += aDeltaTime;
	myDayAngle += myLightConfig.daySpeed * aDeltaTime;
	myCameraController.Update(aDeltaTime);

	AnimateLights();
}
