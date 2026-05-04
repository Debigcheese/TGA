#include "Texture.h"
#include <cassert>

bool Texture::Initialize(ID3D11Device* aDevice, const unsigned char* aRGBAPixels, int aWidth, int aHeight)
{
	assert(aDevice && aRGBAPixels && aWidth > 0 && aHeight > 0);

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = static_cast<UINT>(aWidth);
	desc.Height = static_cast<UINT>(aHeight);
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = aRGBAPixels;
	subData.SysMemPitch = aWidth * 4;
	subData.SysMemSlicePitch = aWidth * aHeight * 4;

	ID3D11Texture2D* texture = nullptr;
	HRESULT hr = aDevice->CreateTexture2D(&desc, &subData, &texture);
	assert(SUCCEEDED(hr) && "Texture: failed to create ID3D11Texture2D");
	if (FAILED(hr)) return false;

	hr = aDevice->CreateShaderResourceView(texture, nullptr, &myShaderResourceView);
	texture->Release();

	assert(SUCCEEDED(hr) && "Texture: failed to create ShaderResourceView");
	return SUCCEEDED(hr);
}

void Texture::Bind(ID3D11DeviceContext* aContext, int aSlot) const
{
	aContext->PSSetShaderResources(static_cast<UINT>(aSlot), 1, myShaderResourceView.GetAddressOf());
}