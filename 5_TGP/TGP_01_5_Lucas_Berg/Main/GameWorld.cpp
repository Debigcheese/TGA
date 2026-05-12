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
				myFileTexture.Initialize(device, rgba.data(), tw, th, false);
			}
			else
			{
				myFileTexture.Initialize(device, img, tw, th, false);
			}
			stbi_image_free(img);
		}
		else
		{

			if (img) stbi_image_free(img);
			// Fallback: solid purple 2x2
			unsigned char fallback[] = { 180,80,220,255, 80,180,220,255, 80,180,220,255, 180,80,220,255 };
			myFileTexture.Initialize(device, fallback, 2, 2, false);
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
		myProceduralTexture.Initialize(device, pixels.data(), Size, Size, false);
	}

	LoadTextureFromFile(device, "textures/Grass_c.png", myGrassColor, true);
	LoadTextureFromFile(device, "textures/Grass_n.png", myGrassNormal, false);
	LoadTextureFromFile(device, "textures/Rock_c.png", myRockColor, true);
	LoadTextureFromFile(device, "textures/Rock_n.png", myRockNormal, false);
	LoadTextureFromFile(device, "textures/Snow_c.png", mySnowColor, true);
	LoadTextureFromFile(device, "textures/Snow_n.png", mySnowNormal, false);

	//objectFactory.LoadObj(device, "craneo", "craneo.obj");

	//auto teapot = objectFactory.CreateGameObject("craneo");
	//teapot.SetShader(ShaderFactory::GetInstance().GetShader("textured"));
	//teapot.SetTexture(&myFileTexture);
	//myObjects.push_back(teapot);

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

	if (!CreateConstantBuffers())
		return false;

	return true;
}

void GameWorld::Render()
{
	auto& engine = *Engine::GetInstance();
	auto context = engine.GetGraphicsEngine().GetContext();

	UpdateFrameBuffer();
	UpdateLightBuffer();

	UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());

	myGrassColor.Bind(context, 0);   // t0
	myRockColor.Bind(context, 1);    // t1
	mySnowColor.Bind(context, 2);    // t2
	myGrassNormal.Bind(context, 3);  // t3
	myRockNormal.Bind(context, 4);   // t4
	mySnowNormal.Bind(context, 5);   // t5

	myTerrain.Render({ context, &myTerrainShader });

	for (auto& obj : myObjects)
	{
		UpdateObjectBuffer(obj.GetTransform());
		obj.Render(context);
	}
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

	return true;
}

bool GameWorld::CreateTextures(ID3D11Device* device)
{
	return false;
}

void GameWorld::UpdateFrameBuffer()
{
	FrameBufferData data = {};
	data.worldToClipMatrix = Matrix4x4f::Transpose(myCamera.GetWorldToClipMatrix());
	data.totalTime = myTotalTime;
	data.cameraPosition = myCamera.GetPosition();

	auto& engine = *Engine::GetInstance();
	auto context = engine.GetGraphicsEngine().GetContext();

	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myFrameBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(FrameBufferData));
	context->Unmap(myFrameBuffer.Get(), 0);

	context->VSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());
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
	data.dirLightDir[0] = dx / dl;
	data.dirLightDir[1] = dy / dl;
	data.dirLightDir[2] = dz / dl;

	float str = FMath::Lerp(c.dirStrengthMin, c.dirStrengthMax, day);
	data.dirLightColor[0] = str * c.dirColorR;
	data.dirLightColor[1] = str * c.dirColorG;
	data.dirLightColor[2] = str * c.dirColorB;

	data.ambientSky[0] = FMath::Lerp(c.ambSkyMinR, c.ambSkyMaxR, day);
	data.ambientSky[1] = FMath::Lerp(c.ambSkyMinG, c.ambSkyMaxG, day);
	data.ambientSky[2] = FMath::Lerp(c.ambSkyMinB, c.ambSkyMaxB, day);

	data.ambientGround[0] = FMath::Lerp(c.ambGndMinR, c.ambGndMaxR, day);
	data.ambientGround[1] = FMath::Lerp(c.ambGndMinG, c.ambGndMaxG, day);
	data.ambientGround[2] = FMath::Lerp(c.ambGndMinB, c.ambGndMaxB, day);

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();

	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myLightBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(LightBufferData));
	context->Unmap(myLightBuffer.Get(), 0);

	context->VSSetConstantBuffers(2, 1, myLightBuffer.GetAddressOf());
	context->PSSetConstantBuffers(2, 1, myLightBuffer.GetAddressOf());
}

bool GameWorld::LoadTextureFromFile(ID3D11Device* device, const char* path, Texture& tex, bool srgb)
{
	int w, h, ch;
	unsigned char* img = stbi_load(path, &w, &h, &ch, 4); // force RGBA
	if (!img) return false;
	bool ok = tex.Initialize(device, img, w, h, srgb);
	stbi_image_free(img);
	return ok;
}

void GameWorld::Update(float aDeltaTime)
{
	myTotalTime += aDeltaTime;
	myDayAngle += myLightConfig.daySpeed * aDeltaTime;
	myCameraController.Update(aDeltaTime);
}