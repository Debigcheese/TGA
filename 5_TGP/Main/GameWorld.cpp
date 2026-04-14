#include "GameWorld.h"

#include <cassert>
#include <iterator>
#include <string>

GameWorld::GameWorld()
{
}

bool GameWorld::Initialize(ID3D11Device* aDevice)
{
	myDevice = aDevice;
	myDevice->GetImmediateContext(&myContext);
	myTriangle = new Triangle();
	return myTriangle->Initialize(aDevice);
}

void GameWorld::Update([[maybe_unused]]float dt)
{
}

void GameWorld::Render()
{

	myTriangle->Render(myContext);
}

bool Triangle::Initialize(ID3D11Device* device)
{
	assert(device && "Device is null");

	HRESULT result;

	Vertex vertices[3] =
	{
		{ -0.8f, -0.8f, 0, 1, 1, 0, 0, 1},
		{  0.0f,  0.8f, 0, 1, 0, 1, 0, 1},
		{  0.8f, -0.8f, 0, 1, 0, 0, 1, 1}
	};

	unsigned int indices[3] = { 0, 1, 2 };

	// Vertex buffer
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(vertices);
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = vertices;

		result = device->CreateBuffer(&desc, &data, &myVertexBuffer);
		if (FAILED(result))
		{
			assert(false && "Failed to create vertex buffer");
			return false;
		}
	}

	// Index buffer
	{
		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(indices);
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = indices;

		result = device->CreateBuffer(&desc, &data, &myIndexBuffer);
		if (FAILED(result))
		{
			assert(false && "Failed to create index buffer");
			return false;
		}
	}

	std::string vsData;

	// Shaders
	{
		std::ifstream vsFile("colored_mesh_VS.cso", std::ios::binary);
		assert(vsFile && "Failed to open VS file");

		vsData = { std::istreambuf_iterator<char>(vsFile), {} };

		result = device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &myVertexShader);
		if (FAILED(result))
		{
			assert(false && "Failed to create vertex shader");
			return false;
		}

		std::ifstream psFile("colored_mesh_PS.cso", std::ios::binary);
		assert(psFile && "Failed to open PS file");

		std::string psData = { std::istreambuf_iterator<char>(psFile), {} };

		result = device->CreatePixelShader(psData.data(), psData.size(), nullptr, &myPixelShader);
		if (FAILED(result))
		{
			assert(false && "Failed to create pixel shader");
			return false;
		}
	}

	// Input layout
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		result = device->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &myInputLayout);
		if (FAILED(result))
		{
			assert(false && "Failed to create input layout");
			return false;
		}
	}

	return true;
}

void Triangle::Render(ID3D11DeviceContext* context)
{
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(myInputLayout.Get());
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;
	context->IASetVertexBuffers(0, 1, myVertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->VSSetShader(myVertexShader.Get(), nullptr, 0);
	context->PSSetShader(myPixelShader.Get(), nullptr, 0);
	context->DrawIndexed(3, 0, 0);

}