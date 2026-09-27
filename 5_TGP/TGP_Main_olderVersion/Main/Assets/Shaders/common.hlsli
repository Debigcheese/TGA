#ifndef COMMON_HLSLI
#define COMMON_HLSLI

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
    float3 emissiveColor;
    float emissiveStrength;
};

#define MAX_LIGHTS_PER_PASS 8

struct PointLightData
{
    float3 position;
    float range;
    float3 color;
    float intensity;
};

struct SpotLightData
{
    float3 position;
    float range;
    float3 direction;
    float cosOuter;
    float3 color;
    float intensity;
    float cosInner;
    float spad0;
    float spad1;
    float spad2;
};

cbuffer LightBuffer : register(b2)
{
    float3 dirLightDir;
    float lp1;
    float3 dirLightColor;
    float dirLightIntensity;

    float3 ambientColor;
    float ambientIntensity;

    float3 ambientGround;
    float padA;

    float3 ambientSky;
    float padB;

    int numEnvMapMipLevels;
    float3 pad0;

    float3 cameraPos;
    float camPad;

    int numPointLights;
    int numSpotLights;
    int isAdditivePass;
    int pad3;

    PointLightData pointLights[MAX_LIGHTS_PER_PASS];
    SpotLightData spotLights[MAX_LIGHTS_PER_PASS];
};

cbuffer ReflectionBuffer : register(b3)
{
    float2 resolution;
    float waterHeight;
    float reflectMode;
};

// ===== TEXTURES =====
TextureCube environmentTexture : register(t0);
Texture2D grassColor : register(t1);
Texture2D rockColor : register(t2);
Texture2D snowColor : register(t3);
Texture2D grassNormal : register(t4);
Texture2D rockNormal : register(t5);
Texture2D snowNormal : register(t6);
Texture2D grassMaterial : register(t7);
Texture2D rockMaterial : register(t8);
Texture2D snowMaterial : register(t9);
Texture2D albedoTexture : register(t10);

// ===== SAMPLER =====
SamplerState defaultSampler : register(s0);

// ===== BASIC MESH TYPES =====
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

// ===== TERRAIN TYPES =====
struct TerrainVSInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

struct TerrainPSInput
{
    float4 position : SV_POSITION;
    float4 worldPosition : POSITION0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float2 uv : TEXCOORD0;
    float clip : SV_ClipDistance0;
};


// ===== UTILS =====
int GetNumMipsCube(TextureCube tex)
{
    return numEnvMapMipLevels;
}

#endif