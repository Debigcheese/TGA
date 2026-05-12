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

VSOut main(VSIn i)
{
    VSOut o;
    float4 wp = mul(float4(i.pos, 1.0), modelToWorldMatrix);
    o.position = mul(wp, worldToClipMatrix);
    o.worldPos = wp.xyz;

    float3x3 m2w = (float3x3) modelToWorldMatrix;
    o.worldNormal = normalize(mul(i.normal, m2w));
    o.worldTangent = normalize(mul(i.tangent, m2w));
    o.worldBitangent = normalize(mul(i.bitangent, m2w));
    o.uv = i.uv;
    return o;
}