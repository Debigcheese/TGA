#include "TerrainMesh.h"
#include "Shader/Shader.h"
#include <cassert>
#include "uppgift_1_5_helper.h"

bool TerrainMesh::Init(ID3D11Device* aDevice,
	const std::vector<TerrainVertex>& aVertices,
	const std::vector<unsigned int>& aIndices)
{
	assert(aDevice);
	myIndexCount = (unsigned int)aIndices.size();

	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = (UINT)(sizeof(TerrainVertex) * aVertices.size());
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA data = {}; data.pSysMem = aVertices.data();
		if (FAILED(aDevice->CreateBuffer(&desc, &data, &myVertexBuffer))) return false;
	}
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = (UINT)(sizeof(unsigned int) * aIndices.size());
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA data = {}; data.pSysMem = aIndices.data();
		if (FAILED(aDevice->CreateBuffer(&desc, &data, &myIndexBuffer))) return false;
	}
	return true;
}

void TerrainMesh::Render(RenderData rd) const
{
	const unsigned int stride = sizeof(TerrainVertex);
	const unsigned int offset = 0;

	rd.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	rd.context->IASetInputLayout(rd.shader->GetInputLayout());
	rd.context->IASetVertexBuffers(0, 1, myVertexBuffer.GetAddressOf(), &stride, &offset);
	rd.context->IASetIndexBuffer(myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	rd.context->VSSetShader(rd.shader->GetVertexShader(), nullptr, 0);
	rd.context->PSSetShader(rd.shader->GetPixelShader(), nullptr, 0);
	rd.context->DrawIndexed(myIndexCount, 0, 0);
}

std::vector<TerrainVertex> TerrainMesh::BuildTerrain(std::vector<unsigned int>& idx, float worldSize, float heightScale)
{
	int res = 4;
	std::vector<float> h(res * res, 0.0f);
	AddNoise(h, 1.0f);
	for (int oct = 0; oct < 6; oct++)
	{
		h = Upsample2X(h, res); res *= 2;
		AddNoise(h, 1.0f / (float)(1 << (oct + 1)));
	}
	// res == 256
	float step = worldSize / (float)(res - 1);
	auto H = [&](int x, int z) -> float
		{
			x = x < 0 ? 0 : x >= res ? res - 1 : x;
			z = z < 0 ? 0 : z >= res ? res - 1 : z;
			return h[z * res + x] * heightScale;
		};
	std::vector<TerrainVertex> verts; verts.reserve(res * res);
	for (int z = 0; z < res; z++) for (int x = 0; x < res; x++)
	{
		TerrainVertex v;
		v.pos = { (float)x * step - worldSize * 0.5f, H(x, z), (float)z * step - worldSize * 0.5f };
		float nx = -(H(x + 1, z) - H(x - 1, z)) / (2 * step);
		float ny = 1.0f;
		float nz = -(H(x, z + 1) - H(x, z - 1)) / (2 * step);
		float nl = sqrtf(nx * nx + ny * ny + nz * nz);
		v.normal = { nx / nl, ny / nl, nz / nl };
		v.uv = { (float)x / (res - 1), (float)z / (res - 1) };
		verts.push_back(v);
	}
	for (int z = 0; z < res - 1; z++) for (int x = 0; x < res - 1; x++)
	{
		unsigned int i00 = z * res + x, i10 = z * res + x + 1;
		unsigned int i01 = (z + 1) * res + x, i11 = (z + 1) * res + x + 1;
		idx.push_back(i00); idx.push_back(i11); idx.push_back(i10);
		idx.push_back(i00); idx.push_back(i01); idx.push_back(i11);
	}
	return verts;
}

