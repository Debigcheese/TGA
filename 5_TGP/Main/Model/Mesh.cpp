#include "Mesh.h"
#include <cassert>

bool Mesh::Init(
	ID3D11Device* aDevice,
	const Vertex* aVertices, unsigned int aVertexCount,
	const unsigned int* aIndices, unsigned int aIndexCount,
	Shader* aShader)
{
	assert(aDevice && "Mesh: device is null");
	assert(aShader && "Mesh: shader is null");

	myIndexCount = aIndexCount;
	myShader = aShader;

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

void Mesh::Render(ID3D11DeviceContext* aContext) const
{
	const unsigned int stride = sizeof(Vertex);
	const unsigned int offset = 0;

	aContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	aContext->IASetInputLayout(myShader->GetInputLayout());
	aContext->IASetVertexBuffers(0, 1, myVertexBuffer.GetAddressOf(), &stride, &offset);
	aContext->IASetIndexBuffer(myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	aContext->VSSetShader(myShader->GetVertexShader(), nullptr, 0);
	aContext->PSSetShader(myShader->GetPixelShader(), nullptr, 0);
	aContext->DrawIndexed(myIndexCount, 0, 0);
}

void Mesh::Render(ID3D11DeviceContext* aContext, Shader* aShader) const
{
	const unsigned int stride = sizeof(Vertex);
	const unsigned int offset = 0;

	aContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	aContext->IASetInputLayout(aShader->GetInputLayout());
	aContext->IASetVertexBuffers(0, 1, myVertexBuffer.GetAddressOf(), &stride, &offset);
	aContext->IASetIndexBuffer(myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	aContext->VSSetShader(aShader->GetVertexShader(), nullptr, 0);
	aContext->PSSetShader(aShader->GetPixelShader(), nullptr, 0);
	aContext->DrawIndexed(myIndexCount, 0, 0);
}
