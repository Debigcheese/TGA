cbuffer FrameBuffer : register(b0)
{
    float4x4 worldToClip;
    float totalTime;
    float3 padding;
};

cbuffer ObjectBuffer : register(b1)
{
    float4x4 modelToWorld;
};

struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    float4 worldPos = mul(input.position, modelToWorld);
    output.position = mul(worldPos, worldToClip);
    output.color = input.color;
    return output;
}