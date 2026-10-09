#ifndef DEFERRED_HLSLI
#define DEFERRED_HLSLI

#include "common.hlsli"

Texture2D gBufferPositionTexture : register(t14);
Texture2D gBufferAlbedoTexture : register(t15);
Texture2D gBufferNormalTexture : register(t16);
Texture2D gBufferMaterialTexture : register(t17);

struct GBufferOutput
{
    float4 worldPosition : SV_TARGET0;
    float4 albedo : SV_TARGET1;
    float4 normal : SV_TARGET2;
    float4 material : SV_TARGET3;
};

struct GBufferData
{
    float4 worldPosition;
    float3 albedo;
    float3 normal;
    float ao;
    float roughness;
    float metalness;
};

GBufferData ReadGBuffer(float4 screenPosition)
{
    int3 pixel = int3(screenPosition.xy, 0);
    float3 material = gBufferMaterialTexture.Load(pixel).rgb;

    GBufferData data;
    data.worldPosition = gBufferPositionTexture.Load(pixel);
    data.albedo = gBufferAlbedoTexture.Load(pixel).rgb;
    data.normal = normalize(gBufferNormalTexture.Load(pixel).xyz * 2.0f - 1.0f);
    data.ao = material.r;
    data.roughness = material.g;
    data.metalness = material.b;
    return data;
}

#endif