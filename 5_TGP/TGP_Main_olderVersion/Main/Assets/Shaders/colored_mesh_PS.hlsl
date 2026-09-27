#include "common.hlsli"

PixelOutput main(PixelInputType input)
{
    PixelOutput result;
    result.color = float4(input.color.rgb, 1.0f);
    return result;
}