#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <string>

using Microsoft::WRL::ComPtr;

class Cubemap
{
public:
	bool Initialize(ID3D11Device* aDevice, const wchar_t* aDDSPath);
	void Bind(ID3D11DeviceContext* aContext, int aSlot) const;
	int  GetNumMips() const { return myNumMips; }
	bool IsValid() const { return mySRV != nullptr; }

private:
	ComPtr<ID3D11ShaderResourceView> mySRV;
	int myNumMips = 0;
};