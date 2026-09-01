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

bool GameWorld::Init()
{
	auto& engine = *Engine::GetInstance();
	auto device = engine.GetGraphicsEngine().GetDevice();
	auto context = engine.GetGraphicsEngine().GetContext();
	assert(device && "device null");
	assert(context && "context null");
	if (!myCamera.Initialize(90.0f, { (float)engine.GetGraphicsEngine().GetWidth(),
									  (float)engine.GetGraphicsEngine().GetHeight() }, 0.1f, 1000.0f))
		return false;

	myCamera.SetPosition({ 0.0f, 1.0f, -4.0f });
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
			unsigned char fallback[] = { 180,80,220,255, 80,180,220,255, 80,180,220,255, 180,80,220,255 };
			myFileTexture.Initialize(device, context, fallback, 2, 2, false);
		}
	}

	// checkerboard 
	{
		constexpr int Size = 64, Cells = 8;
		std::vector<unsigned char> pixels(Size * Size * 4);
		for (int y = 0; y < Size; ++y)
			for (int x = 0; x < Size; ++x)
			{
				bool white = ((x * Cells / Size) + (y * Cells / Size)) % 2 == 0;
				int i = (y * Size + x) * 4;
				pixels[i + 0] = pixels[i + 1] = pixels[i + 2] = white ? 230 : 30;
				pixels[i + 3] = 255;
			}
		myProceduralTexture.Initialize(device, context, pixels.data(), Size, Size, false);

	}

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

	for (int i = 0; i < 5; i++)
	{
		auto cube = objectFactory.CreateGameObject("Cube");
		cube.SetPosition({ 0,(float)i,0 });

		Shader* shader = nullptr;
		Texture* texture = nullptr;
		i % 2 == 0 ? shader = ShaderFactory::GetInstance().GetShader("lit")
			: shader = ShaderFactory::GetInstance().GetShader("animated");
		i % 2 == 0 ? texture = &myProceduralTexture : texture = &myFileTexture;

		cube.SetTexture(texture);
		cube.SetShader(shader);
		myObjects.push_back(cube);
	}

	auto pyramid = objectFactory.CreateGameObject("Pyramid");
	pyramid.SetPosition({ 2, 0, 0 });
	pyramid.SetTexture(&myFileTexture);
	pyramid.SetShader(ShaderFactory::GetInstance().GetShader("animated"));

	myObjects.push_back(pyramid);

	auto& ge = engine.GetGraphicsEngine();
	if (!myReflectionRT.Initialize(device, ge.GetWidth(), ge.GetHeight()))
		return false;

	myWaterObject = objectFactory.CreateGameObject("Plane");
	myWaterObject.SetShader(ShaderFactory::GetInstance().GetShader("water"));
	myWaterObject.SetScale(100.0f);
	myWaterObject.SetPosition({ 0.0f, myWaterHeight, 0.0f });

	if (!CreateConstantBuffers())
		return false;

	return true;
}
void GameWorld::Render()
{
    auto& engine = *Engine::GetInstance();
    auto& ge = engine.GetGraphicsEngine();
    auto context = ge.GetContext();

    UpdateLightBuffer();

    //  PASS 1: Reflektion till render target 
    UpdateReflectionBuffer((float)ge.GetWidth(), (float)ge.GetHeight(), 
                          myWaterHeight, 1.0f); // reflectMode = 1.0

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
	
    // Rendera terräng (med clip plane aktiv via reflectMode=1.0)
    UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
    BindTerrainTextures(context);
    myTerrain.Render({ context, &myTerrainShader });

    // Rendera objekt (om de ska synas i reflektion)
    for (auto& obj : myObjects)
    {
        UpdateObjectBuffer(obj.GetTransform());
        obj.Render(context);
    }

    //  PASS 2: Vanlig scen 
    // Återställ backbuffer och normal culling
    ID3D11RenderTargetView* backRTV = ge.GetBackBufferRTV();
    context->OMSetRenderTargets(1, &backRTV, ge.GetDepthBufferDSV());
    context->ClearDepthStencilView(ge.GetDepthBufferDSV(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    context->RSSetState(nullptr); 

    UpdateReflectionBuffer((float)ge.GetWidth(), (float)ge.GetHeight(),
                          myWaterHeight, 0.0f); 

    UpdateFrameBuffer(myCamera.GetWorldToClipMatrix());

    UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
    BindTerrainTextures(context);
    myTerrain.Render({ context, &myTerrainShader });

    for (auto& obj : myObjects)
    {
        UpdateObjectBuffer(obj.GetTransform());
        obj.Render(context);
    }

    // PASS 3: Vatten 
    myReflectionRT.BindAsTexture(context, 11);
    
    UpdateObjectBuffer(myWaterObject.GetTransform());
    myWaterObject.Render(context);

    ID3D11ShaderResourceView* nullSRV = nullptr;
    context->PSSetShaderResources(11, 1, &nullSRV);
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

bool GameWorld::CreateTextures(ID3D11Device* device)
{
	return false;
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
	myGrassColor.Bind(context, 1);  myRockColor.Bind(context, 2);  mySnowColor.Bind(context, 3);
	myGrassNormal.Bind(context, 4); myRockNormal.Bind(context, 5); mySnowNormal.Bind(context, 6);
	myGrassMaterial.Bind(context, 7); myRockMaterial.Bind(context, 8); mySnowMaterial.Bind(context, 9);
}

void GameWorld::UpdateObjectBuffer(const Matrix4x4f& aModelToWorld)
{
	ObjectBufferData data = {};
	data.modelToWorldMatrix = Matrix4x4f::Transpose(aModelToWorld);

	auto& engine = *Engine::GetInstance();
	auto context = engine.GetGraphicsEngine().GetContext();

	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myObjectBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(ObjectBufferData));
	context->Unmap(myObjectBuffer.Get(), 0);

	context->VSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
}

void GameWorld::UpdateLightBuffer()
{
	auto& c = myLightConfig;

	float sunY = cosf(myDayAngle);
	float sunX = sinf(myDayAngle);

	float shifted = sunY + c.dayShift;
	float day = FMath::Saturate(shifted / c.dayRange);
	day = day * day * (3.0f - 2.0f * day);

	float dx = sunX;
	float dy = sunY;
	float dz = c.sunDirZ;
	float dl = sqrtf(dx * dx + dy * dy + dz * dz);

	LightBufferData data = {};

	// Directional light direction (from sun position)
	data.dirLightDir[0] = dx / dl;
	data.dirLightDir[1] = dy / dl;
	data.dirLightDir[2] = dz / dl;

	// Directional light color + intensity
	float str = FMath::Lerp(c.dirStrengthMin, c.dirStrengthMax, day);
	data.dirLightColor[0] = c.dirColorR;
	data.dirLightColor[1] = c.dirColorG;
	data.dirLightColor[2] = c.dirColorB;
	data.dirLightIntensity = str;

	// Ambient (cubemap modulation)
	data.ambientColor[0] = 1.0f;
	data.ambientColor[1] = 1.0f;
	data.ambientColor[2] = 1.0f;
	data.ambientIntensity = 1.0f;

	data.numEnvMapMipLevels = myEnvironmentCubemap.GetNumMips();

	// Camera position for view direction in PBR
	data.cameraPosition[0] = myCamera.GetPosition().x;
	data.cameraPosition[1] = myCamera.GetPosition().y;
	data.cameraPosition[2] = myCamera.GetPosition().z;

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
		assert("LoadTextureFromFile: failed to load file");
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
}