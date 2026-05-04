#include "common.hlsli"

struct PSIn
{
    float4 position : SV_POSITION;
    float4 worldPos : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float3 worldNormal : NORMAL;
};

float4 main(PSIn i) : SV_TARGET
{
    float3 N = normalize(i.worldNormal);
    float upFac = N.y * 0.5 + 0.5;
    float3 ambient = lerp(ambientGround, ambientSky, upFac);
    float3 diffuse = dirLightColor * saturate(dot(N, dirLightDir));
    float4 texCol = albedoTexture.Sample(defaultSampler, i.uv);
    return float4(texCol.rgb * i.color.rgb * (ambient + diffuse), texCol.a);
}