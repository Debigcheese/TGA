#include "GraphicsEngine.h"
#include <cassert>

#define REPORT_DX_WARNINGS

GraphicsEngine::GraphicsEngine() = default;
GraphicsEngine::~GraphicsEngine() = default;

bool GraphicsEngine::Init(HWND aWindowHandle, const GraphicsConfig& aConfig)
{
	HRESULT result;

	myConfig = aConfig;
	// Swap chain & device 
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = aConfig.bufferCount;
	swapChainDesc.BufferDesc.Format = aConfig.backBufferFormat;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SampleDesc.Count = aConfig.sampleCount;
	swapChainDesc.SampleDesc.Quality = aConfig.sampleQuality;
	swapChainDesc.OutputWindow = aWindowHandle;
	swapChainDesc.Windowed = !aConfig.fullscreen;

	UINT creationFlags = 0;
#if defined(REPORT_DX_WARNINGS)
	if (aConfig.enableDXDebug)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&mySwapChain,
		&myDevice,
		nullptr,
		&myContext
	);
	assert(SUCCEEDED(result) && "Failed to create device and swap chain");
	if (FAILED(result)) return false;

	// Back buffer render target 
	ID3D11Texture2D* backBufferTexture = nullptr;
	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);
	assert(SUCCEEDED(result) && "Failed to get back buffer");
	if (FAILED(result)) return false;

	result = myDevice->CreateRenderTargetView(backBufferTexture, nullptr, &myBackBuffer);
	assert(SUCCEEDED(result) && "Failed to create render target view");
	if (FAILED(result)) { backBufferTexture->Release(); return false; }

	D3D11_TEXTURE2D_DESC backBufferDesc;
	backBufferTexture->GetDesc(&backBufferDesc);
	backBufferTexture->Release();

	myConfig.width = backBufferDesc.Width;
	myConfig.height = backBufferDesc.Height;

	// Depth buffer 
	D3D11_TEXTURE2D_DESC depthDesc = {};
	depthDesc.Width = myConfig.width;
	depthDesc.Height = myConfig.height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* depthTexture = nullptr;
	result = myDevice->CreateTexture2D(&depthDesc, nullptr, &depthTexture);
	assert(SUCCEEDED(result) && "Failed to create depth texture");
	if (FAILED(result)) return false;

	result = myDevice->CreateDepthStencilView(depthTexture, nullptr, &myDepthBuffer);
	assert(SUCCEEDED(result) && "Failed to create depth stencil view");
	depthTexture->Release();
	if (FAILED(result)) return false;

	// Bind render target + depth buffer 
	myContext->OMSetRenderTargets(1, myBackBuffer.GetAddressOf(), myDepthBuffer.Get());

	// Viewport 
	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(myConfig.width);
	viewport.Height = static_cast<float>(myConfig.height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	myContext->RSSetViewports(1, &viewport);

	if (!CreateSamplerState())
		return false;

	D3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FrontCounterClockwise = false;

	myDevice->CreateRasterizerState(&rastDesc, &myRasterizerState);
	myContext->RSSetState(myRasterizerState.Get());

	return true;
}

void GraphicsEngine::BeginFrame()
{
	myContext->ClearRenderTargetView(myBackBuffer.Get(), myConfig.backgroundColor);
	myContext->ClearDepthStencilView(myDepthBuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicsEngine::EndFrame()
{
	mySwapChain->Present(myConfig.vsync ? 1 : 0, 0);
}

bool GraphicsEngine::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.MinLOD = 0.0f;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = myDevice->CreateSamplerState(&desc, &mySamplerState);
	assert(SUCCEEDED(hr) && "Failed to create sampler state");
	if (FAILED(hr)) return false;

	// Bind once – all pixel shaders share this sampler at slot s0
	myContext->PSSetSamplers(0, 1, mySamplerState.GetAddressOf());
	return true;
}
