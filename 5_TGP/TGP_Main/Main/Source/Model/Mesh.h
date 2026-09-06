#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Vertex.h"

using Microsoft::WRL::ComPtr;
class Texture;
class Shader;

class Mesh
{
public:
	struct RenderData
	{
		ID3D11DeviceContext* context;
		Shader* shader;
		Texture* texture;
	};

	Mesh() = default;
	~Mesh() = default;

	bool Init(
		ID3D11Device* aDevice,
		const Vertex* aVertices, unsigned int aVertexCount,
		const unsigned int* aIndices, unsigned int aIndexCount
	);

	void Render(RenderData aRenderData) const;

	unsigned int GetIndexCount() const { return myIndexCount; }

	static void SetFallbackTexture(const Texture* aTexture) { ourFallbackTexture = aTexture; }

private:
	static inline const Texture* ourFallbackTexture = nullptr;
	ComPtr<ID3D11Buffer> myVertexBuffer;
	ComPtr<ID3D11Buffer> myIndexBuffer;

	unsigned int myIndexCount = 0;
};
