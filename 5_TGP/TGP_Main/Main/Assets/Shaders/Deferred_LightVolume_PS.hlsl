#include "Deferred.hlsli"
#include "PBRFunctions.hlsli"

float4 main(PixelInputType input) : SV_TARGET
{
    GBufferData gBuffer = ReadGBuffer(input.position);

    float3 pixelPosition = gBuffer.worldPosition.xyz;
    float3 toEye = normalize(cameraPos - pixelPosition);
    float3 specularColor = lerp((float3) 0.04f, gBuffer.albedo, gBuffer.metalness);
    float3 diffuseColor = lerp((float3) 0.05f, gBuffer.albedo, 1.0f - gBuffer.metalness);

    float3 result = 0.0f;

    for (int p = 0; p < numPointLights; ++p)
    {
        result += EvaluatePointLight(diffuseColor, specularColor, gBuffer.normal, gBuffer.roughness,
            pointLights[p].color, pointLights[p].intensity, pointLights[p].range, pointLights[p].position,
            toEye, pixelPosition);
    }

    for (int s = 0; s < numSpotLights; ++s)
    {
        float3 toLight = normalize(spotLights[s].position - pixelPosition);
        float cone = smoothstep(spotLights[s].cosOuter, spotLights[s].cosInner, dot(spotLights[s].direction, -toLight));

        result += cone * EvaluatePointLight(diffuseColor, specularColor, gBuffer.normal, gBuffer.roughness,
            spotLights[s].color, spotLights[s].intensity, spotLights[s].range, spotLights[s].position,
            toEye, pixelPosition);
    }

    return float4(result, 1.0f);
}