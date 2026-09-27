#include "common.hlsli"
#include "pbrfunctions.hlsli"

Texture2D reflectionTexture : register(t11);

float4 main(PixelInputType input) : SV_TARGET
{
    float3 normal = normalize(input.color.xyz);
    float3 toEye = normalize(cameraPosition - input.worldPosition.xyz);
    
    float3 fresnel = Fresnel_Schlick(float3(0.02, 0.02, 0.02), normal, toEye);
    
    float2 uv = input.position.xy / resolution;
    float2 worldXZ = input.worldPosition.xz;
    float time = totalTime;
    
    float wave1 = sin(dot(worldXZ, float2(6, 4)) + time);
    float wave2 = sin(dot(worldXZ, float2(3, 8)) + time * 0.7);
    float wave3 = sin(dot(worldXZ, float2(12, 2)) + time * 1.3);
    
    float waves = wave1 * 0.5 + wave2 * 0.3 + wave3 * 0.2;
    
    float2 offset = float2(
        cos(worldXZ.x * 6 + time) * 0.00015,
        cos(worldXZ.y * 4 + time) * 0.00015
    );
    
    float dist = length(input.worldPosition.xyz - cameraPosition);
    offset *= saturate(10.0 / dist);
    
    float3 reflection = reflectionTexture.SampleLevel(defaultSampler, uv + offset, abs(waves) * 0.5).rgb;
    float3 water = lerp(float3(0.02, 0.08, 0.15), float3(0.05, 0.15, 0.25), saturate(dot(toEye, normal)));
    
    water += waves * 0.02 * float3(0.1, 0.2, 0.3);
    
    float3 color = lerp(water, reflection, fresnel.x);
    
    float3 halfVec = normalize(toEye + float3(0, 1, 0));
    color += pow(saturate(dot(normal, halfVec)), 128.0) * 0.3;
    
    return float4(color, lerp(0.6, 0.95, fresnel.x));
}