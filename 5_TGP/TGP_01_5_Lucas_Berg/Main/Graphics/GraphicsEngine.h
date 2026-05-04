#pragma once
#include <wrl/client.h>
#include <d3d11.h>

using Microsoft::WRL::ComPtr;

struct GraphicsConfig
{
	// Window
	int width = 1280;
	int height = 720;
	bool fullscreen = false;
	bool vsync = true; // (1,0) vs (0,0)

	// Back buffer
	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	int bufferCount = 1; // 1 = single, 2 = double buffering

	// Background Color 
	float backgroundColor[4] = { 0.1f, 0.1f, 0.15f, 1.0f };

	// Depth buffer
	DXGI_FORMAT depthFormat = DXGI_FORMAT_D32_FLOAT;

	// MSAA (multisampling / anti-aliasing)
	int sampleCount = 1; // 1 = off, 4 = 4x MSAA
	int sampleQuality = 0;

	// Debug
	bool enableDXDebug = true; // D3D11_CREATE_DEVICE_DEBUG
};

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	bool Init(HWND aWindowHandle, const GraphicsConfig& aConfig);

	void BeginFrame();
	void EndFrame();

	ID3D11Device* GetDevice() const { return myDevice.Get(); }
	ID3D11DeviceContext* GetContext() const { return myContext.Get(); }
	unsigned int GetWidth() const { return myConfig.width; }
	unsigned int GetHeight() const { return myConfig.height; }

private:
	bool CreateSamplerState();
	//could be in its own dx11 class ? later make graphics engine behave like a container instead
	ComPtr<ID3D11Device>			myDevice;
	ComPtr<ID3D11DeviceContext>		myContext;
	ComPtr<IDXGISwapChain>			mySwapChain;
	ComPtr<ID3D11RenderTargetView>	myBackBuffer;
	ComPtr<ID3D11DepthStencilView>	myDepthBuffer;
	ComPtr<ID3D11SamplerState>		mySamplerState;
	ComPtr<ID3D11RasterizerState> myRasterizerState;

	GraphicsConfig myConfig;
};