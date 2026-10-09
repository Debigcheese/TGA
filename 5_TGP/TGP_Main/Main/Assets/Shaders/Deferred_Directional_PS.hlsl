#include "Deferred.hlsli"
#include "PBRFunctions.hlsli"

struct FullscreenInput
{
    float4 position : SV_POSITION;
    float2 uv : UV;
};

float4 main(FullscreenInput input) : SV_TARGET
{
    GBufferData gBuffer = ReadGBuffer(input.position);
    if (gBuffer.worldPosition.w == 0.0f)
        discard;

    float3 toEye = normalize(cameraPos - gBuffer.worldPosition.xyz);
    float3 specularColor = lerp((float3) 0.04f, gBuffer.albedo, gBuffer.metalness);
    float3 diffuseColor = lerp((float3) 0.05f, gBuffer.albedo, 1.0f - gBuffer.metalness);

    float3 ambiance = EvaluateAmbiance(environmentTexture, gBuffer.normal, gBuffer.normal, toEye,
        gBuffer.roughness, gBuffer.ao, diffuseColor, specularColor);

    float3 direct = EvaluateDirectionalLight(diffuseColor, specularColor, gBuffer.normal, gBuffer.roughness,
        dirLightColor * dirLightIntensity, normalize(-dirLightDir), toEye);

    return float4(ambiance * ambientIntensity + direct, 1.0f);
}