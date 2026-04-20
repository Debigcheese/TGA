#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Vertex.h"
#include "Shader/Shader.h"

using Microsoft::WRL::ComPtr;

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

	bool Init(
		ID3D11Device* aDevice,
		const Vertex* aVertices, unsigned int aVertexCount,
		const unsigned int* aIndices, unsigned int aIndexCount,
		Shader* aShader
	);

	void Render(ID3D11DeviceContext* aContext) const;
	void Render(ID3D11DeviceContext* aContext, Shader* aShader) const;

	unsigned int GetIndexCount() const { return myIndexCount; }
	void SetShader(Shader* aShader) { myShader = aShader; }

private:
	ComPtr<ID3D11Buffer> myVertexBuffer;
	ComPtr<ID3D11Buffer> myIndexBuffer;

	Shader* myShader = nullptr;
	unsigned int myIndexCount = 0;
};