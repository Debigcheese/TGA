#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <string>

using Microsoft::WRL::ComPtr;

class Shader
{
public:
	enum class Layout
	{
		Default,
		Terrain,
	};

	bool Init(ID3D11Device* aDevice,
		const std::string& aVSPath,
		const std::string& aPSPath,
		Layout aLayout = Layout::Default);

	ID3D11VertexShader* GetVertexShader() const { return myVertexShader.Get(); }
	ID3D11PixelShader* GetPixelShader()  const { return myPixelShader.Get(); }
	ID3D11InputLayout* GetInputLayout()  const { return myInputLayout.Get(); }

private:
	ComPtr<ID3D11VertexShader> myVertexShader;
	ComPtr<ID3D11PixelShader>  myPixelShader;
	ComPtr<ID3D11InputLayout>  myInputLayout;
};