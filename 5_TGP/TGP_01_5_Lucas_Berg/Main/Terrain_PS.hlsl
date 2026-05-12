#include "common.hlsli"

Texture2D grassColor : register(t0);
Texture2D rockColor : register(t1);
Texture2D snowColor : register(t2);
Texture2D grassNormal : register(t3);
Texture2D rockNormal : register(t4);
Texture2D snowNormal : register(t5);
SamplerState samp : register(s0);

struct PSIn
{
    float4 position : SV_POSITION;
    float3 worldNormal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
    float3 worldTangent : TEXCOORD2;
    float3 worldBitangent : TEXCOORD3;
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
    float3 T = normalize(i.worldTangent);
    float3 B = normalize(i.worldBitangent);
    float3 N = normalize(i.worldNormal);
    float3x3 TBN = float3x3(T, B, N); // rows = T, B, N

    // Tile UVs for repeating textures
    float2 tiledUV = i.uv * 20.0;

    // Sample albedos
    float3 grassCol = grassColor.Sample(samp, tiledUV).rgb;
    float3 rockCol = rockColor.Sample(samp, tiledUV).rgb;
    float3 snowCol = snowColor.Sample(samp, tiledUV).rgb;

    // Sample normal maps (stored as RG, reconstruct Z)
    // If your textures store full XYZ in RGB, use all three channels
    float3 grassN = grassNormal.Sample(samp, tiledUV).rgb;
    float3 rockN = rockNormal.Sample(samp, tiledUV).rgb;
    float3 snowN = snowNormal.Sample(samp, tiledUV).rgb;

    // Unpack from [0,1] to [-1,1]
    grassN = grassN * 2.0 - 1.0;
    rockN = rockN * 2.0 - 1.0;
    snowN = snowN * 2.0 - 1.0;

    // If TGE-packed (only XY, reconstruct Z):
    // grassN.z = sqrt(1.0 - saturate(grassN.x*grassN.x + grassN.y*grassN.y));

    // Blend based on slope and height (from the lecture)
    float slopeBlend = smoothstep(0.7, 1.0, N.y);
    float heightBlend = smoothstep(-0.05, 0.25, i.worldPos.y);

    float3 albedo = lerp(rockCol, lerp(grassCol, snowCol, heightBlend), slopeBlend);
    float3 blendedNormal = lerp(rockN, lerp(grassN, snowN, heightBlend), slopeBlend);

    // Transform from tangent space to world space
    float3 finalN = normalize(mul(blendedNormal, TBN));

    // Lighting
    float upFac = finalN.y * 0.5 + 0.5;
    float3 ambient = lerp(ambientGround, ambientSky, upFac);
    float3 diffuse = dirLightColor * saturate(dot(finalN, dirLightDir));

    return float4(albedo * (ambient + diffuse), 1.0);
}