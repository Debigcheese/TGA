#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Lights.h"
#include <algorithm>

using Microsoft::WRL::ComPtr;

class RenderTarget
{
public:
	bool Initialize(ID3D11Device* device, UINT width, UINT height,
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM)
	{
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = format;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

		ComPtr<ID3D11Texture2D> texture;
		if (FAILED(device->CreateTexture2D(&desc, nullptr, &texture))) return false;
		if (FAILED(device->CreateRenderTargetView(texture.Get(), nullptr, &myRTV))) return false;
		if (FAILED(device->CreateShaderResourceView(texture.Get(), nullptr, &mySRV))) return false;
		return true;
	}

	void SetAsTarget(ID3D11DeviceContext* c, ID3D11DepthStencilView* dsv)
	{
		c->OMSetRenderTargets(1, myRTV.GetAddressOf(), dsv);
	}

	void Clear(ID3D11DeviceContext* c, const float color[4])
	{
		c->ClearRenderTargetView(myRTV.Get(), color);
	}

	void BindAsTexture(ID3D11DeviceContext* c, UINT slot)
	{
		c->PSSetShaderResources(slot, 1, mySRV.GetAddressOf());
	}

private:
	ComPtr<ID3D11RenderTargetView> myRTV;
	ComPtr<ID3D11ShaderResourceView> mySRV;
};
