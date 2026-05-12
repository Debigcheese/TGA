#include "Shader.h"
#include <fstream>
#include <iterator>
#include <cassert>

bool Shader::Init(ID3D11Device* aDevice,
	const std::string& aVSPath,
	const std::string& aPSPath,
	Layout aLayout)
{
	HRESULT result;

	std::ifstream vsFile(aVSPath, std::ios::binary);
	assert(vsFile && "Shader: failed to open vertex shader");
	if (!vsFile) return false;
	std::string vsData = { std::istreambuf_iterator<char>(vsFile), {} };

	result = aDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &myVertexShader);
	assert(SUCCEEDED(result) && "Shader: failed to create vertex shader");
	if (FAILED(result)) return false;

	std::ifstream psFile(aPSPath, std::ios::binary);
	assert(psFile && "Shader: failed to open pixel shader");
	if (!psFile) return false;
	std::string psData = { std::istreambuf_iterator<char>(psFile), {} };

	result = aDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &myPixelShader);
	assert(SUCCEEDED(result) && "Shader: failed to create pixel shader");
	if (FAILED(result)) return false;

	if (aLayout == Layout::Default)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		result = aDevice->CreateInputLayout(layout, 4, vsData.data(), vsData.size(), &myInputLayout);
	}
	else
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		result = aDevice->CreateInputLayout(layout, 5, vsData.data(), vsData.size(), &myInputLayout);
	}

	assert(SUCCEEDED(result) && "Shader: failed to create input layout");
	if (FAILED(result)) return false;

	return true;
}