#include "common.hlsli"

struct VSIn
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VSOut
{
    float4 position : SV_POSITION;
    float3 worldNormal : NORMAL;
    float2 uv : TEXCOORD;
    float3 worldPos : TEXCOORD1;
};

VSOut main(VSIn i)
{
    VSOut o;
    float4 wp = mul(float4(i.pos, 1.0), modelToWorldMatrix);
    o.position = mul(wp, worldToClipMatrix);
    o.worldPos = wp.xyz;
    o.worldNormal = normalize(mul(i.normal, (float3x3) modelToWorldMatrix));
    o.uv = i.uv;
    return o;
}