#pragma once
#include <array>
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

namespace GBufferTexture
{
	enum : int
	{
		WorldPosition = 0,
		Albedo,
		Normal,
		Material,
		Count
	};
}

class GBuffer
{
public:
	bool Initialize(ID3D11Device* aDevice, UINT aWidth, UINT aHeight);

	void SetAsTarget(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer) const;
	void Clear(ID3D11DeviceContext* aContext) const;
	void BindAsTextures(ID3D11DeviceContext* aContext, UINT aStartSlot) const;
	void UnbindTextures(ID3D11DeviceContext* aContext, UINT aStartSlot) const;

private:
	std::array<ComPtr<ID3D11RenderTargetView>, GBufferTexture::Count> myRTVs;
	std::array<ComPtr<ID3D11ShaderResourceView>, GBufferTexture::Count> mySRVs;
};
