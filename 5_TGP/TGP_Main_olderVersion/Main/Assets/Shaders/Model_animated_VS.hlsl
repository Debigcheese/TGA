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
    float3 p = i.position.xyz;

    // Apex wobble
    float apexMask = saturate((p.y - 0.3) / 0.7);
    p.y += sin(totalTime * 3.0) * 0.25 * apexMask;

    // Self-rotation around Y
    float s = sin(totalTime * 1.2), c = cos(totalTime * 1.2);
    float3 rp = float3(p.x * c + p.z * s, p.y, -p.x * s + p.z * c);
    float3 rn = float3(i.normal.x * c + i.normal.z * s, i.normal.y, -i.normal.x * s + i.normal.z * c);

    float4 wp = mul(float4(rp, 1.0), modelToWorldMatrix);
    o.position = mul(wp, worldToClipMatrix);
    o.worldPos = wp;
    o.color = i.color;
    o.uv = i.uv;
    o.worldNormal = normalize(mul(rn, (float3x3) modelToWorldMatrix));
    return o;
}