#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "main.h"
#include <fstream>

using Microsoft::WRL::ComPtr;

class Triangle;

class GameWorld
{
public:
	GameWorld();

	bool Initialize(ID3D11Device* aDevice);
	void Update(float dt);
	void Render();

private:
	Triangle* myTriangle;
	ID3D11Device *myDevice;
	ID3D11DeviceContext* myContext;
};

class Triangle
{
	struct Vertex
	{
		float x, y, z, w;
		float r, g, b, a;
	};
public:
	Triangle() = default;
	~Triangle() = default;

	bool Initialize(ID3D11Device*);
	void Render(ID3D11DeviceContext*);
private:
	ComPtr<ID3D11Buffer> myVertexBuffer;
	ComPtr<ID3D11Buffer> myIndexBuffer;
	ComPtr<ID3D11VertexShader> myVertexShader;
	ComPtr<ID3D11PixelShader> myPixelShader;
	ComPtr<ID3D11InputLayout> myInputLayout;
};