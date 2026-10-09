#include "Deferred.hlsli"

GBufferOutput main(TerrainPSInput input)
{
    float2 uv = input.uv * 20.0f;

    float3 grassCol = grassColor.Sample(defaultSampler, uv).rgb;
    float3 rockCol = rockColor.Sample(defaultSampler, uv).rgb;
    float3 snowCol = snowColor.Sample(defaultSampler, uv).rgb;

    float3 grassN = grassNormal.Sample(defaultSampler, uv).rgb;
    float3 rockN = rockNormal.Sample(defaultSampler, uv).rgb;
    float3 snowN = snowNormal.Sample(defaultSampler, uv).rgb;

    float3 grassM = grassMaterial.Sample(defaultSampler, uv).rgb;
    float3 rockM = rockMaterial.Sample(defaultSampler, uv).rgb;
    float3 snowM = snowMaterial.Sample(defaultSampler, uv).rgb;

    float3 Nw = normalize(input.normal);
    float slopeBlend = smoothstep(0.7f, 1.0f, Nw.y);
    float heightBlend = smoothstep(-0.015f, 0.25f, input.worldPosition.y);

    float3 albedo = lerp(rockCol, lerp(grassCol, snowCol, heightBlend), slopeBlend);
    float3 blendedN = lerp(rockN, lerp(grassN, snowN, heightBlend), slopeBlend);
    float3 blendedM = lerp(rockM, lerp(grassM, snowM, heightBlend), slopeBlend);

    blendedN = blendedN * 2.0f - 1.0f;
    blendedN.z = sqrt(1.0f - saturate(dot(blendedN.xy, blendedN.xy)));
    blendedN = normalize(blendedN);

    float3x3 TBN = float3x3(normalize(input.tangent), normalize(input.binormal), Nw);
    float3 N = normalize(mul(blendedN, TBN));

    GBufferOutput output;
    output.worldPosition = float4(input.worldPosition.xyz, 1.0f);
    output.albedo = float4(albedo, 1.0f);
    output.normal = float4(N * 0.5f + 0.5f, 1.0f);
    output.material = float4(blendedM, 1.0f);
    return output;
}