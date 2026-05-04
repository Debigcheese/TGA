#include "common.hlsli"

struct VSIn
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct VSOut
{
    float4 position : SV_POSITION;
    float4 worldPos : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float3 worldNormal : NORMAL;
};

VSOut main(VSIn i)
{
    VSOut o;
    float4 wp = mul(i.position, modelToWorldMatrix);
    o.position = mul(wp, worldToClipMatrix);
    o.worldPos = wp;
    o.color = i.color;
    o.uv = i.uv;
    o.worldNormal = normalize(mul(i.normal, (float3x3) modelToWorldMatrix));
    return o;
}