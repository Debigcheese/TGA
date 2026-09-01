#include "Texture.h"
#include <cassert>


bool Texture::Initialize(ID3D11Device* aDevice, ID3D11DeviceContext* aContext,
	const unsigned char* aRGBAPixels, int aWidth, int aHeight, bool aUseSrgb)
{
	assert(aDevice && aContext && aRGBAPixels && aWidth > 0 && aHeight > 0);

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = static_cast<UINT>(aWidth);
	desc.Height = static_cast<UINT>(aHeight);
	desc.MipLevels = 0;                                  // 0 = full mip chain
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;                    // NOT IMMUTABLE
	desc.Format = aUseSrgb ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB
		: DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	ID3D11Texture2D* texture = nullptr;
	HRESULT hr = aDevice->CreateTexture2D(&desc, nullptr, &texture);
	assert(SUCCEEDED(hr) && "Texture: failed to create ID3D11Texture2D");
	if (FAILED(hr)) return false;

	aContext->UpdateSubresource(texture, 0, nullptr, aRGBAPixels, aWidth * 4, 0);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;                    // all mips

	hr = aDevice->CreateShaderResourceView(texture, &srvDesc, &myShaderResourceView);
	texture->Release();

	assert(SUCCEEDED(hr) && "Texture: failed to create ShaderResourceView");
	if (FAILED(hr)) return false;

	aContext->GenerateMips(myShaderResourceView.Get());
	return true;
}

void Texture::Bind(ID3D11DeviceContext* aContext, int aSlot) const
{
	aContext->PSSetShaderResources(static_cast<UINT>(aSlot), 1, myShaderResourceView.GetAddressOf());
}