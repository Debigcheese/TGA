#include "Cubemap.h"
#include <cassert>
#include "DDSTextureLoader11.h"

bool Cubemap::Initialize(ID3D11Device* aDevice, const wchar_t* aDDSPath)
{
	assert(aDevice && aDDSPath);

	ComPtr<ID3D11Resource> resource;
	HRESULT hr = DirectX::CreateDDSTextureFromFile(
		aDevice, aDDSPath,
		resource.GetAddressOf(),
		mySRV.GetAddressOf());

	if (FAILED(hr)) return false;

	// Get mip count
	ComPtr<ID3D11Texture2D> tex;
	resource.As(&tex);
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);
	myNumMips = (int)desc.MipLevels;

	return true;
}

void Cubemap::Bind(ID3D11DeviceContext* aContext, int aSlot) const
{
	aContext->PSSetShaderResources((UINT)aSlot, 1, mySRV.GetAddressOf());
}