#include "common.hlsli"

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    
    float4 worldPos = mul(input.position, modelToWorldMatrix);
    output.worldPosition = worldPos;
    output.position = mul(worldPos, worldToClipMatrix);
    
    float3 worldNormal = mul(float3(0,1,0), (float3x3)modelToWorldMatrix);
    output.color = float4(worldNormal, 1.0f);
    
    output.uv = input.uv;
    
    return output;
}