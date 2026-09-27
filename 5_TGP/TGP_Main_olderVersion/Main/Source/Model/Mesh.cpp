#include "Mesh.h"
#include "Texture.h"
#include <cassert>
#include "Shader/Shader.h"

bool Mesh::Init(
	ID3D11Device* aDevice,
	const Vertex* aVertices, unsigned int aVertexCount,
	const unsigned int* aIndices, unsigned int aIndexCount)
{
	assert(aDevice && "Mesh: device is null");
	myIndexCount = aIndexCount;

	HRESULT result;
	// Vertex buffer
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(Vertex) * aVertexCount;
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = aVertices;

		result = aDevice->CreateBuffer(&desc, &data, &myVertexBuffer);
		assert(SUCCEEDED(result) && "Mesh: failed to create vertex buffer");
		if (FAILED(result)) return false;
	}

	// Index buffer
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(unsigned int) * aIndexCount;
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = aIndices;

		result = aDevice->CreateBuffer(&desc, &data, &myIndexBuffer);
		assert(SUCCEEDED(result) && "Mesh: failed to create index buffer");
		if (FAILED(result)) return false;
	}

	return true;
}

void Mesh::Render(RenderData aRenderData) const
{
	const Texture* tex = aRenderData.texture ? aRenderData.texture : ourFallbackTexture;
	if (tex)
		tex->Bind(aRenderData.context, 10);

	const unsigned int stride = sizeof(Vertex);
	const unsigned int offset = 0;

	aRenderData.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	aRenderData.context->IASetInputLayout(aRenderData.shader->GetInputLayout());
	aRenderData.context->IASetVertexBuffers(0, 1, myVertexBuffer.GetAddressOf(), &stride, &offset);
	aRenderData.context->IASetIndexBuffer(myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	aRenderData.context->VSSetShader(aRenderData.shader->GetVertexShader(), nullptr, 0);
	aRenderData.context->PSSetShader(aRenderData.shader->GetPixelShader(), nullptr, 0);
	aRenderData.context->DrawIndexed(myIndexCount, 0, 0);
}
