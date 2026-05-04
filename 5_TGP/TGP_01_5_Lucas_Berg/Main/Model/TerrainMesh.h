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
	Vector3<float> pos;
	Vector3<float> normal;
	Vector2<float> uv;
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

	static std::vector<TerrainVertex> BuildTerrain(std::vector<unsigned int>& idx,
		float worldSize, float heightScale);
private:
	ComPtr<ID3D11Buffer> myVertexBuffer;
	ComPtr<ID3D11Buffer> myIndexBuffer;
	unsigned int myIndexCount = 0;
};