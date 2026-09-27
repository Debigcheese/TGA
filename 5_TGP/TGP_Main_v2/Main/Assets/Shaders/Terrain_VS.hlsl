#include "common.hlsli"

struct VSIn
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float3 tangent : TANGENT;
    float3 bitangent : BINORMAL;
};

struct VSOut
{
    float4 position : SV_POSITION;
    float3 worldNormal : NORMAL;
    float2 uv : TEXCOORD;
    float3 worldPos : TEXCOORD1;
    float3 worldTangent : TEXCOORD2;
    float3 worldBitangent : TEXCOORD3;
};

TerrainPSInput main(TerrainVSInput input)
{
    TerrainPSInput output;
    
    float4 worldPos = mul(float4(input.position, 1.0f), modelToWorldMatrix);
    output.worldPosition = worldPos;
    output.position = mul(worldPos, worldToClipMatrix);
    
    output.normal = mul(input.normal, (float3x3) modelToWorldMatrix);
    output.tangent = mul(input.tangent, (float3x3) modelToWorldMatrix);
    output.binormal = mul(input.binormal, (float3x3) modelToWorldMatrix);
    output.uv = input.uv;
    
    output.clip = (reflectMode > 0.5f)
        ? (worldPos.y - waterHeight) // Under vatten = negativt = klipp
        : 1.0f; // Normalt, ingen clipping
    
    return output;
}