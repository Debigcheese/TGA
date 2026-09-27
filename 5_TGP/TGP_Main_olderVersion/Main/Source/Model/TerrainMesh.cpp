#include "TerrainMesh.h"
#include "Shader/Shader.h"
#include <cassert>
#include "uppgift_1_5_helper.h"
#include <algorithm>

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

std::vector<TerrainVertex> TerrainMesh::BuildTerrain(std::vector<unsigned int>& idx)
{
	TerrainConfig cfg = {};
	int res = 4;
	std::vector<float> h(res * res, 0.0f);
	AddNoise(h, 1.0f);
	for (int oct = 0; oct < cfg.octaves; oct++)
	{
		h = Upsample2X(h, res); res *= 2;
		AddNoise(h, 1.0f / (float)(1 << (oct + cfg.falloffPower)));
	}

	for (int pass = 0; pass < cfg.smoothPasses; pass++)
	{
		std::vector<float> smoothed(res * res, 0.0f);
		for (int z = 0; z < res; z++)
			for (int x = 0; x < res; x++)
			{
				float sum = 0.0f;
				int count = 0;
				for (int dz = -1; dz <= 1; dz++)
					for (int dx = -1; dx <= 1; dx++)
					{
						int sx = std::clamp(x + dx, 0, res - 1);
						int sz = std::clamp(z + dz, 0, res - 1);
						sum += h[sz * res + sx];
						count++;
					}
				smoothed[z * res + x] = sum / count;
			}
		h = smoothed;
	}

	float step = cfg.worldSize / (float)(res - 1);
	auto H = [&](int x, int z) -> float
		{
			x = x < 0 ? 0 : x >= res ? res - 1 : x;
			z = z < 0 ? 0 : z >= res ? res - 1 : z;
			return h[z * res + x] * cfg.heightScale;
		};

	std::vector<TerrainVertex> verts; verts.reserve(res * res);
	for (int z = 0; z < res; z++) for (int x = 0; x < res; x++)
	{
		TerrainVertex v;
		v.pos = { (float)x * step - cfg.worldSize * 0.5f, H(x, z), (float)z * step - cfg.worldSize * 0.5f };
		float nx = -(H(x + 1, z) - H(x - 1, z)) / (2 * step);
		float ny = 1.0f;
		float nz = -(H(x, z + 1) - H(x, z - 1)) / (2 * step);
		float nl = sqrtf(nx * nx + ny * ny + nz * nz);
		v.normal = { nx / nl, ny / nl, nz / nl };

		Tga::Vector3f N(v.normal.x, v.normal.y, v.normal.z);
		Tga::Vector3f up(0.f, 0.f, 1.f);

		Tga::Vector3f T = N.Cross(up);
		if (T.LengthSqr() < 0.0001f)
			T = { 1.f, 0.f, 0.f };
		T.Normalize();

		Tga::Vector3f B = N.Cross(T);
		B.Normalize();

		v.tangent = { T.x, T.y, T.z };
		v.bitangent = { B.x, B.y, B.z };
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

