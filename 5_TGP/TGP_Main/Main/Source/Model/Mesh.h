#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Vertex.h"

using Microsoft::WRL::ComPtr;
class Shader;

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

	bool Init(
		ID3D11Device* aDevice,
		const Vertex* aVertices, unsigned int aVertexCount,
		const unsigned int* aIndices, unsigned int aIndexCount
	);

	void Render(ID3D11DeviceContext* aContext, const Shader* aShader) const;

	unsigned int GetIndexCount() const { return myIndexCount; }

private:
	ComPtr<ID3D11Buffer> myVertexBuffer;
	ComPtr<ID3D11Buffer> myIndexBuffer;

	unsigned int myIndexCount = 0;
};
