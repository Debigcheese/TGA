#include "common.hlsli"

PixelOutput main(PixelInputType input)
{
    PixelOutput result;
    float pulse = (sin(totalTime * 3.0f) * 0.5f) + 0.5f;
    result.color = float4(input.color.rgb * pulse, 1.0f);
    return result;
}