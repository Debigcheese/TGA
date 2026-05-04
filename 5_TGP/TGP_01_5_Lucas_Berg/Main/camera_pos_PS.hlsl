#include "common.hlsli"

PixelOutput main(PixelInputType input)
{
    PixelOutput result;
    
    float dist = distance(cameraPosition, input.worldPosition.xyz);
    float fog = saturate(dist / 8.0f);
    
    float4 texColor = albedoTexture.Sample(defaultSampler, input.uv);
    result.color = lerp(texColor, float4(0, 0, 0, 1), fog);
    return result;
}