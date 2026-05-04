Texture2D albedoTexture : register(t0);
Texture2D normalTexture : register(t1);
SamplerState defaultSampler : register(s0);

cbuffer FrameBuffer : register(b0)
{
    float4x4 worldToClipMatrix;
    float totalTime;
    float3 framePad;
    float3 cameraPosition;
    float camerapad;
};

cbuffer ObjectBuffer : register(b1)
{
    float4x4 modelToWorldMatrix;
};

cbuffer LightBuffer : register(b2)
{
    float3 dirLightDir;
    float lp1;
    float3 dirLightColor;
    float lp2;
    float3 ambientSky;
    float lp3;
    float3 ambientGround;
    float lp4;
};

struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 worldPosition : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

struct PixelOutput
{
    float4 color : SV_TARGET;
};