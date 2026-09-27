#include "common.hlsli"

PixelOutput main(PixelInputType input)
{
    PixelOutput result;
    result.color = albedoTexture.Sample(defaultSampler, input.uv);
    return result;
}