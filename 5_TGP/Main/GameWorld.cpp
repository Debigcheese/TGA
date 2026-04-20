#include "GameWorld.h"
#include "Engine.h"
#include <cassert>
#include <cstring>
#include "Shader/ShaderFactory.h"

bool GameWorld::Init()
{
	auto& engine = *Engine::GetInstance();
	auto device = engine.GetGraphicsEngine().GetDevice();

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

	for (int i = 0; i < 5; i++)
	{
		auto cube = objectFactory.CreateGameObject("Cube");
		cube.SetPosition({ 0,(float)i,0 });

		Shader* shader = nullptr;
		i % 2 == 0 ? shader = ShaderFactory::GetInstance().GetShader("animated") : shader = ShaderFactory::GetInstance().GetShader("colored");

		cube.SetShader(shader);
		myObjects.push_back(cube);
	}

	auto pyramid = objectFactory.CreateGameObject("Pyramid");
	pyramid.SetPosition({ 2, 0, 0 });
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

	return true;
}

void GameWorld::UpdateFrameBuffer()
{
	FrameBufferData data = {};
	data.worldToClipMatrix = Matrix4x4f::Transpose(myCamera.GetWorldToClipMatrix());
	data.totalTime = myTotalTime;

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

void GameWorld::Update(float aDeltaTime)
{
	myTotalTime += aDeltaTime;
	myCameraController.Update(aDeltaTime);
}

