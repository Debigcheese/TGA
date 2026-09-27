#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>
#include "CommonUtilities/math/Vector3.h"
#include "CommonUtilities/math/Vector2.h"

using Microsoft::WRL::ComPtr;
using namespace Tga;

struct TerrainVertex
{
	Tga::Vector3f pos;
	Tga::Vector3f normal;
	Tga::Vector2f uv;
	Tga::Vector3f tangent;
	Tga::Vector3f bitangent;
};

struct TerrainConfig
{
	float worldSize = 200.0f;
	float heightScale = 20.0f;
	int   octaves = 6;
	int   smoothPasses = 3;
	float uvTiling = 20.0f;  // for shader tiling

	// Noise amplitude falloff per octave: 1 / (1 << (oct + falloffPower))
	int   falloffPower = 1;
};

class Shader;

class TerrainMesh
{
public:
	struct RenderData
	{
		ID3D11DeviceContext* context;
		Shader* shader;
	};

	bool Init(ID3D11Device* aDevice,
		const std::vector<TerrainVertex>& aVertices,
		const std::vector<unsigned int>& aIndices);

	void Render(RenderData aRenderData) const;

	std::vector<TerrainVertex> BuildTerrain(std::vector<unsigned int>& idx);
private:
	ComPtr<ID3D11Buffer> myVertexBuffer;
	ComPtr<ID3D11Buffer> myIndexBuffer;
	unsigned int myIndexCount = 0;
};