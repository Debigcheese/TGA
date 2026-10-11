#include "Graphics/GraphicsRenderer.h"
#include "Engine.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>

#include "Scene.h"
#include "Camera/Camera.h"

#include "CommonUtilities/TransformUtils.h"

bool GraphicsRenderer::Init()
{
	if (!CreateConstantBuffers())
		return false;

	if (!CreateRenderStates())
		return false;

	if (!CreateShaders())
		return false;

	if (!CreateRenderTargets())
		return false;

	myLightVolume = GameObjectFactory::GetInstance().CreateGameObject("Cube");
	myLightVolume.SetShader(&myDeferredShaders[DeferredShader::LightVolume]);

	return true;
}

void GraphicsRenderer::Render(const Scene& aScene, const Camera& aCamera, float aTotalTime)
{
	myScene = &aScene;
	myCamera = &aCamera;
	myTotalTime = aTotalTime;

	auto& graphicsEngine = Engine::GetInstance()->GetGraphicsEngine();
	auto context = graphicsEngine.GetContext();
	ID3D11RenderTargetView* backBuffer = graphicsEngine.GetBackBufferRTV();
	ID3D11DepthStencilView* depthBuffer = graphicsEngine.GetDepthBufferDSV();
	ID3D11ShaderResourceView* nullSRV = nullptr;

	RenderReflection(context, depthBuffer);

	context->ClearDepthStencilView(depthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->RSSetState(nullptr);

	UpdateReflectionBuffer((float)graphicsEngine.GetWidth(), (float)graphicsEngine.GetHeight(),
	                       myScene->GetWaterHeight(), 0.0f);
	UpdateFrameBuffer(myCamera->GetWorldToClipMatrix());

	RenderGBuffer(context, depthBuffer);
	RenderDeferredLighting(context, depthBuffer);

	context->OMSetRenderTargets(1, &backBuffer, nullptr);
	mySceneRT.BindAsTexture(context, 0);
	RenderFullscreen(context, myDeferredShaders[DeferredShader::Tonemap]);
	context->PSSetShaderResources(0, 1, &nullSRV);

	context->OMSetRenderTargets(1, &backBuffer, depthBuffer);
	context->RSSetState(myNoCullRasterizerState.Get());
	RenderLightMarkers(context);
	context->RSSetState(nullptr);

	RenderWater(context);
}

bool GraphicsRenderer::CreateConstantBuffers()
{
	auto device = Engine::GetInstance()->GetGraphicsEngine().GetDevice();

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	desc.ByteWidth = sizeof(FrameBufferData);
	if (FAILED(device->CreateBuffer(&desc, nullptr, &myFrameBuffer)))
		return false;

	desc.ByteWidth = sizeof(ObjectBufferData);
	if (FAILED(device->CreateBuffer(&desc, nullptr, &myObjectBuffer)))
		return false;

	desc.ByteWidth = sizeof(LightBufferData);
	if (FAILED(device->CreateBuffer(&desc, nullptr, &myLightBuffer)))
		return false;

	desc.ByteWidth = sizeof(ReflectionBufferData);
	if (FAILED(device->CreateBuffer(&desc, nullptr, &myReflectionBuffer)))
		return false;

	return true;
}

bool GraphicsRenderer::CreateRenderStates()
{
	auto& ge = Engine::GetInstance()->GetGraphicsEngine();
	auto device = ge.GetDevice();

	D3D11_SAMPLER_DESC sd = {};
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(device->CreateSamplerState(&sd, &mySampler)))
		return false;
	ge.GetContext()->PSSetSamplers(0, 1, mySampler.GetAddressOf());

	D3D11_BLEND_DESC bd = {};
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if (FAILED(device->CreateBlendState(&bd, &myAdditiveBlendState)))
		return false;

	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsd.DepthFunc = D3D11_COMPARISON_GREATER;
	dsd.StencilEnable = false;
	if (FAILED(device->CreateDepthStencilState(&dsd, &myReadOnlyGreaterDepthState)))
		return false;

	D3D11_RASTERIZER_DESC rd = {};
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.DepthClipEnable = true;
	if (FAILED(device->CreateRasterizerState(&rd, &myNoCullRasterizerState)))
		return false;

	rd.CullMode = D3D11_CULL_FRONT;
	if (FAILED(device->CreateRasterizerState(&rd, &myFrontFaceCullingRasterizerState)))
		return false;

	return true;
}

bool GraphicsRenderer::CreateShaders()
{
	auto device = Engine::GetInstance()->GetGraphicsEngine().GetDevice();

	if (!myTerrainShader.Init(device, "terrain_VS.cso", "terrain_PS.cso", Shader::Layout::Terrain))
		return false;

	const struct
	{
		std::string vertexShader;
		std::string pixelShader;
		Shader::Layout layout;
	}
	deferredShaders[DeferredShader::Count] = {
		{"model_lit_VS.cso", "Model_GBuffer_PS.cso", Shader::Layout::Default},
		{"terrain_VS.cso", "Terrain_GBuffer_PS.cso", Shader::Layout::Terrain},
		{"Fullscreen_VS.cso", "Deferred_Directional_PS.cso", Shader::Layout::None},
		{"default_VS.cso", "Deferred_LightVolume_PS.cso", Shader::Layout::Default},
		{"Fullscreen_VS.cso", "PostprocessTonemapPS.cso", Shader::Layout::None},
	};
	for (int i = 0; i < DeferredShader::Count; ++i)
	{
		const auto& desc = deferredShaders[i];
		if (!myDeferredShaders[i].Init(device, desc.vertexShader, desc.pixelShader, desc.layout))
			return false;
	}

	return true;
}

bool GraphicsRenderer::CreateRenderTargets()
{
	auto& ge = Engine::GetInstance()->GetGraphicsEngine();
	auto device = ge.GetDevice();

	if (!myReflectionRT.Initialize(device, ge.GetWidth(), ge.GetHeight()))
		return false;

	if (!myGBuffer.Initialize(device, ge.GetWidth(), ge.GetHeight()))
		return false;

	if (!mySceneRT.Initialize(device, ge.GetWidth(), ge.GetHeight(), DXGI_FORMAT_R16G16B16A16_FLOAT))
		return false;

	return true;
}

void GraphicsRenderer::UpdateFrameBuffer(const Matrix4x4f& aWorldToClip)
{
	FrameBufferData data = {};
	data.worldToClipMatrix = Matrix4x4f::Transpose(aWorldToClip);
	data.totalTime = myTotalTime;
	data.cameraPosition = myCamera->GetPosition();

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myFrameBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(FrameBufferData));
	context->Unmap(myFrameBuffer.Get(), 0);

	context->VSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());
}

void GraphicsRenderer::UpdateObjectBuffer(const Matrix4x4f& aModelToWorld, const Vector3f& anEmissiveColor,
                                          float anEmissiveStrength)
{
	ObjectBufferData data = {};
	data.modelToWorldMatrix = Matrix4x4f::Transpose(aModelToWorld);
	data.emissiveColor = anEmissiveColor;
	data.emissiveStrength = anEmissiveStrength;

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myObjectBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(ObjectBufferData));
	context->Unmap(myObjectBuffer.Get(), 0);

	context->VSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
	context->PSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
}

void GraphicsRenderer::UpdateLightBuffer(const std::vector<LightRef>& someLights, bool anAdditivePass)
{
	const DirectionalLightConfig& directionalLight = myScene->GetDirectionalLight();
	const std::vector<PointLight>& pointLights = myScene->GetPointLights();
	const std::vector<SpotLight>& spotLights = myScene->GetSpotLights();

	LightBufferData data = {};
	data.dirLightDirection = directionalLight.direction.GetNormalized();
	data.dirLightColor = directionalLight.color;
	data.dirLightIntensity = directionalLight.intensity;
	data.ambientSky = directionalLight.ambientSky;
	data.ambientGround = directionalLight.ambientGround;
	data.numEnvMapMipLevels = myScene->GetEnvironmentCubemap().GetNumMips();
	data.cameraPosition = myCamera->GetPosition();
	data.isAdditivePass = anAdditivePass ? 1 : 0;
	data.ambientIntensity = directionalLight.ambientIntensity;

	for (const LightRef& ref : someLights)
	{
		if (ref.isSpot)
		{
			const SpotLight& spot = spotLights[ref.index];
			data.spotLights[data.numSpotLights++] = {
				spot.position, spot.range, spot.direction.GetNormalized(), cosf(spot.outerAngle),
				spot.color, spot.intensity, cosf(spot.innerAngle)
			};
		}
		else
		{
			const PointLight& point = pointLights[ref.index];
			data.pointLights[data.numPointLights++] = {point.position, point.range, point.color, point.intensity};
		}
	}

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myLightBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(LightBufferData));
	context->Unmap(myLightBuffer.Get(), 0);

	context->VSSetConstantBuffers(2, 1, myLightBuffer.GetAddressOf());
	context->PSSetConstantBuffers(2, 1, myLightBuffer.GetAddressOf());
}

void GraphicsRenderer::UpdateReflectionBuffer(float aResolutionX, float aResolutionY, float aWaterHeight,
                                              float aReflectMode)
{
	ReflectionBufferData data = {};
	data.resolution[0] = aResolutionX;
	data.resolution[1] = aResolutionY;
	data.waterHeight = aWaterHeight;
	data.reflectMode = aReflectMode;

	auto context = Engine::GetInstance()->GetGraphicsEngine().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	context->Map(myReflectionBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &data, sizeof(ReflectionBufferData));
	context->Unmap(myReflectionBuffer.Get(), 0);

	context->VSSetConstantBuffers(3, 1, myReflectionBuffer.GetAddressOf());
	context->PSSetConstantBuffers(3, 1, myReflectionBuffer.GetAddressOf());
}

void GraphicsRenderer::BindTerrainTextures(ID3D11DeviceContext* aContext)
{
	myScene->GetEnvironmentCubemap().Bind(aContext, 0);
	for (int i = 0; i < TERRAIN_TEXTURE_COUNT; ++i)
	{
		myScene->GetTerrainTexture(i)->Bind(aContext, i + 1);
	}
}

void GraphicsRenderer::RenderReflection(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer)
{
	auto& graphicsEngine = Engine::GetInstance()->GetGraphicsEngine();
	const float waterHeight = myScene->GetWaterHeight();

	UpdateLightBuffer({}, false);
	UpdateReflectionBuffer((float)graphicsEngine.GetWidth(), (float)graphicsEngine.GetHeight(), waterHeight, 1.0f);

	aContext->RSSetState(myFrontFaceCullingRasterizerState.Get());

	const float reflectionClearColor[4] = {0.45f, 0.6f, 0.75f, 1.0f};
	myReflectionRT.SetAsTarget(aContext, aDepthBuffer);
	myReflectionRT.Clear(aContext, reflectionClearColor);
	aContext->ClearDepthStencilView(aDepthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Matrix4x4f reflectionMatrix = Matrix4x4f::CreateIdentityMatrix();
	reflectionMatrix(2, 2) = -1.0f;
	reflectionMatrix(4, 2) = 2.0f * waterHeight;
	UpdateFrameBuffer(reflectionMatrix * myCamera->GetViewMatrix() * myCamera->GetProjectionMatrix());

	UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
	BindTerrainTextures(aContext);
	myScene->GetTerrain().Render({aContext, &myTerrainShader});

	for (const auto& obj : myScene->GetObjects())
	{
		UpdateObjectBuffer(obj.GetTransform());
		obj.Render(aContext);
	}
}

void GraphicsRenderer::RenderGBuffer(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer)
{
	myGBuffer.Clear(aContext);
	myGBuffer.SetAsTarget(aContext, aDepthBuffer);

	UpdateObjectBuffer(Matrix4x4f::CreateIdentityMatrix());
	BindTerrainTextures(aContext);
	myScene->GetTerrain().Render({aContext, &myDeferredShaders[DeferredShader::TerrainGBuffer]});

	aContext->RSSetState(myNoCullRasterizerState.Get());

	for (const auto& obj : myScene->GetObjects())
	{
		UpdateObjectBuffer(obj.GetTransform());
		obj.Render(aContext, &myDeferredShaders[DeferredShader::ModelGBuffer]);
	}

	aContext->RSSetState(nullptr);
}

void GraphicsRenderer::RenderDeferredLighting(ID3D11DeviceContext* aContext, ID3D11DepthStencilView* aDepthBuffer)
{
	const float sceneClearColor[4] = {0.1f, 0.1f, 0.15f, 1.0f};
	mySceneRT.SetAsTarget(aContext, nullptr);
	mySceneRT.Clear(aContext, sceneClearColor);

	myGBuffer.BindAsTextures(aContext, GBUFFER_TEXTURE_SLOT);
	myScene->GetEnvironmentCubemap().Bind(aContext, 0);

	UpdateLightBuffer({}, false);
	RenderFullscreen(aContext, myDeferredShaders[DeferredShader::DirectionalLight]);

	const float blendFactor[4] = {};
	mySceneRT.SetAsTarget(aContext, aDepthBuffer);
	aContext->OMSetBlendState(myAdditiveBlendState.Get(), blendFactor, 0xFFFFFFFF);
	aContext->OMSetDepthStencilState(myReadOnlyGreaterDepthState.Get(), 0);
	aContext->RSSetState(myFrontFaceCullingRasterizerState.Get());

	RenderLightVolumes(aContext);

	aContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	aContext->OMSetDepthStencilState(nullptr, 0);
	aContext->RSSetState(nullptr);

	myGBuffer.UnbindTextures(aContext, GBUFFER_TEXTURE_SLOT);
}

void GraphicsRenderer::RenderLightVolumes(ID3D11DeviceContext* aContext)
{
	const std::vector<PointLight>& pointLights = myScene->GetPointLights();
	const std::vector<SpotLight>& spotLights = myScene->GetSpotLights();

	for (int i = 0; i < (int)pointLights.size(); ++i)
	{
		const float size = pointLights[i].range * 2.0f;
		UpdateLightBuffer({LightRef{false, i, 0.0f}}, true);
		UpdateObjectBuffer(BuildBoxTransform(pointLights[i].position, {size, size, size}));
		myLightVolume.Render(aContext);
	}

	for (int i = 0; i < (int)spotLights.size(); ++i)
	{
		const float size = spotLights[i].range * 2.0f;
		UpdateLightBuffer({LightRef{true, i, 0.0f}}, true);
		UpdateObjectBuffer(BuildBoxTransform(spotLights[i].position, {size, size, size}));
		myLightVolume.Render(aContext);
	}
}

void GraphicsRenderer::RenderLightMarkers(ID3D11DeviceContext* aContext)
{
	UpdateLightBuffer({}, false);

	for (const auto& l : myScene->GetPointLights())
	{
		UpdateObjectBuffer(BuildBoxTransform(l.position, {0.8f, 0.8f, 0.8f}), l.color, 1.0f);
		myScene->GetPointMarker().Render(aContext);
	}

	for (const auto& l : myScene->GetSpotLights())
	{
		UpdateObjectBuffer(BuildAimedTransform(l.position, l.direction, 1.5f), l.color, 1.5f);
		myScene->GetSpotMarker().Render(aContext);
	}
}

void GraphicsRenderer::RenderWater(ID3D11DeviceContext* aContext)
{
	ID3D11ShaderResourceView* nullSRV = nullptr;
	const GameObject& water = myScene->GetWaterObject();

	UpdateLightBuffer({}, false);
	myReflectionRT.BindAsTexture(aContext, 11);
	UpdateObjectBuffer(water.GetTransform());
	water.Render(aContext);
	aContext->PSSetShaderResources(11, 1, &nullSRV);
}

void GraphicsRenderer::RenderObjectWithLights(ID3D11DeviceContext* aContext, const GameObject& anObject)
{
	const Matrix4x4f& transform = anObject.GetTransform();
	const std::vector<LightRef> lights = myScene->CollectLightsForObject(transform.GetPosition(), anObject.GetRadius());
	UpdateObjectBuffer(transform);

	size_t start = 0;
	while (start == 0 || start < lights.size())
	{
		const size_t end = std::min(start + MAX_LIGHTS_PER_PASS, lights.size());
		const std::vector<LightRef> chunk(lights.begin() + start, lights.begin() + end);
		const bool additive = start > 0;

		if (additive)
		{
			const float blendFactor[4] = {};
			aContext->OMSetBlendState(myAdditiveBlendState.Get(), blendFactor, 0xFFFFFFFF);
			aContext->OMSetDepthStencilState(myAdditiveDepthState.Get(), 0);
		}

		UpdateLightBuffer(chunk, additive);
		anObject.Render(aContext);

		if (end == start)
			break;
		start = end;
	}

	aContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	aContext->OMSetDepthStencilState(nullptr, 0);
}

void GraphicsRenderer::RenderFullscreen(ID3D11DeviceContext* aContext, const Shader& aShader)
{
	aContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	aContext->IASetInputLayout(nullptr);
	aContext->VSSetShader(aShader.GetVertexShader(), nullptr, 0);
	aContext->PSSetShader(aShader.GetPixelShader(), nullptr, 0);
	aContext->Draw(3, 0);
}
