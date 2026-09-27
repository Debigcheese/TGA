#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class Texture
{
public:
	Texture() = default;
	~Texture() = default;

	// Initialize from raw RGBA pixel data (4 bytes per pixel).
	bool Initialize(ID3D11Device* aDevice, ID3D11DeviceContext* aContext,
		const unsigned char* aRGBAPixels, int aWidth, int aHeight, bool aUseSrgb);

	// Bind the texture to the pixel shader at the given slot (t0, t1, …).
	void Bind(ID3D11DeviceContext* aContext, int aSlot) const;

	bool IsValid() const { return myShaderResourceView != nullptr; }

private:
	ComPtr<ID3D11ShaderResourceView> myShaderResourceView;
};