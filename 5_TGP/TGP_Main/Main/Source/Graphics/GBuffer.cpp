#include "GBuffer.h"
#include <cassert>

bool GBuffer::Initialize(ID3D11Device* aDevice, UINT aWidth, UINT aHeight)
{
	const DXGI_FORMAT formats[GBufferTexture::Count] =
	{
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		DXGI_FORMAT_R10G10B10A2_UNORM,
		DXGI_FORMAT_R8G8B8A8_UNORM,
	};

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = aWidth;
	desc.Height = aHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	for (int i = 0; i < GBufferTexture::Count; ++i)
	{
		desc.Format = formats[i];

		ComPtr<ID3D11Texture2D> texture;
		HRESULT result = aDevice->CreateTexture2D(&desc, nullptr, &texture);
		assert(SUCCEEDED(result) && "GBuffer: failed to create texture");
		if (FAILED(result)) return false;

		result = aDevice->CreateRenderTargetView(texture.Get(), nullptr, &myRTVs[i]);
		assert(SUCCEEDED(result) && "GBuffer: failed to create render target view");
		if (FAILED(result)) return false;

		result = aDevice->CreateShaderResourceView(texture.Get(), nullptr, &mySRVs[i]);
		assert(SUCCEEDED(result) && "GBuffer: failed to create shader resource view");
		if (FAILED(result)) return false;
	}

	return true;
}

void GBuffer::SetAsTarget(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer) const
{
	aContext->OMSetRenderTargets(GBufferTexture::Count, myRTVs[0].GetAddressOf(), aDepthBuffer);
}

void GBuffer::Clear(ID3D11DeviceContext* aContext) const
{
	const float clearColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	for (const auto& rtv : myRTVs)
	{
		aContext->ClearRenderTargetView(rtv.Get(), clearColor);
	}
}

void GBuffer::BindAsTextures(ID3D11DeviceContext* aContext, UINT aStartSlot) const
{
	aContext->PSSetShaderResources(aStartSlot, GBufferTexture::Count, mySRVs[0].GetAddressOf());
}

void GBuffer::UnbindTextures(ID3D11DeviceContext* aContext, UINT aStartSlot) const
{
	ID3D11ShaderResourceView* nullSRVs[GBufferTexture::Count] = {};
	aContext->PSSetShaderResources(aStartSlot, GBufferTexture::Count, nullSRVs);
}
