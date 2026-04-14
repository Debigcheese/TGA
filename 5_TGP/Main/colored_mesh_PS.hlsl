//float4 main() : SV_TARGET
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}

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
    result.color = input.color;
    result.color = float4(result.color.r, result.color.g, result.color.b , 1.0f);
    return result;
}