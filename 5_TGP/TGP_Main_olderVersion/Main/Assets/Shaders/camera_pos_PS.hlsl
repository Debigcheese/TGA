#include "common.hlsli"

struct PSIn
{
    float4 position : SV_POSITION;
    float4 worldPos : POSITION0;
    float2 uv : TEXCOORD0;
};

float4 main(PSIn i) : SV_TARGET
{
    float dist = distance(cameraPosition, i.worldPos.xyz);
    float fog = saturate(dist / 8.0f);

    float4 texColor = albedoTexture.Sample(defaultSampler, i.uv);

    return lerp(texColor, float4(0, 0, 0, 1), fog);
}