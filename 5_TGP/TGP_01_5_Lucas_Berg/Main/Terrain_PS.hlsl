#include "common.hlsli"

struct PSIn
{
    float4 position : SV_POSITION;
    float3 worldNormal : NORMAL;
    float2 uv : TEXCOORD;
    float3 worldPos : TEXCOORD1;
};

float3 TerrainAlbedo(float height, float2 uv)
{
    float check = fmod(floor(uv.x * 20.0) + floor(uv.y * 20.0), 2.0);
    float3 grass = lerp(float3(0.25, 0.55, 0.15), float3(0.30, 0.62, 0.20), check * 0.15);
    float3 rock = float3(0.50, 0.45, 0.38);
    float3 snow = float3(0.90, 0.92, 0.95);
    float3 col = lerp(grass, rock, saturate((height - 5.0) / 10.0));
    return lerp(col, snow, saturate((height - 15.0) / 5.0));
}

float4 main(PSIn i) : SV_TARGET
{
    float3 N = normalize(i.worldNormal);
    float upFac = N.y * 0.5 + 0.5;
    float3 ambient = lerp(ambientGround, ambientSky, upFac);
    float3 diffuse = dirLightColor * saturate(dot(N, dirLightDir));
    float3 albedo = TerrainAlbedo(i.worldPos.y, i.uv);
    return float4(albedo * (ambient + diffuse), 1.0);
}