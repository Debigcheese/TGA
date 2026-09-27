#include "common.hlsli"

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    float4 worldPos = mul(input.position, modelToWorldMatrix);
    output.position = mul(worldPos, worldToClipMatrix);
    output.worldPosition = worldPos;
    output.color = input.color;
    output.uv = input.uv;
    return output;
}