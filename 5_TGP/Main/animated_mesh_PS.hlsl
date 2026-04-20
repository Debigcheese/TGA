cbuffer FrameBuffer : register(b0)
{
    float4x4 worldToClip;
    float totalTime;
    float3 padding;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct PixelOutput
{
    float4 color : SV_TARGET;
};

PixelOutput main(PixelInputType input)
{
    PixelOutput result;
    float pulse = (sin(totalTime * 3.0f) * 0.5f) + 0.5f;
    result.color = float4(input.color.rgb * pulse, 1.0f);
    return result;
}