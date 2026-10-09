#include "common.hlsli"

struct VSIn
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

struct VSOut
{
    float4 position : SV_POSITION;
    float4 worldPos : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float3 worldNormal : NORMAL;
    float3 worldTangent : TANGENT;
    float3 worldBinormal : BINORMAL;
};

VSOut main(VSIn i)
{
    VSOut result;
    float4 wp = mul(i.position, modelToWorldMatrix);
    result.position = mul(wp, worldToClipMatrix);
    result.worldPos = wp;
    result.color = i.color;
    result.uv = i.uv;
    result.worldNormal = normalize(mul(i.normal, (float3x3) modelToWorldMatrix));
    result.worldTangent = mul(i.tangent, (float3x3) modelToWorldMatrix);
    result.worldBinormal = mul(i.binormal, (float3x3) modelToWorldMatrix);
    return result;
}