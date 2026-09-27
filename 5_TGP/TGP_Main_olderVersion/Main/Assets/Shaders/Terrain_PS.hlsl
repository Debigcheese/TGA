#include "Common.hlsli"
#include "PBRFunctions.hlsli"
#include "Tonemap.hlsli"

#define DEBUG_MODE 0

struct Layer
{
    float3 albedo;
    float3 normalTex;
    float ao;
    float metalness;
    float roughness;
};

Layer SampleLayer(Texture2D cTex, Texture2D nTex, Texture2D mTex, float2 uv)
{
    Layer L;
    L.albedo = cTex.Sample(defaultSampler, uv).rgb;
    L.normalTex = nTex.Sample(defaultSampler, uv).rgb;
    float3 m = mTex.Sample(defaultSampler, uv).rgb;
    L.ao = m.r;
    L.roughness = m.g;
    L.metalness = m.b;
    return L;
}

float3 SmoothDirectionalSpecular(float3 specularColor, float3 N, float3 toEye,
    float roughness, float3 lightColor, float lightIntensity, float3 lightDir)
{
    float3 lDir = normalize(-lightDir);
    float3 halfVec = normalize(lDir + toEye);
    float NdH = max(0.0, dot(N, halfVec));
    float specPower = 2.0 / (roughness * roughness * roughness * roughness) - 2.0;
    float spec = pow(NdH, max(specPower, 1.0));

    float NdL = dot(N, lDir) * 0.5 + 0.5;
    NdL = NdL * NdL;

    return specularColor * spec * NdL * lightColor * lightIntensity;
}

float4 main(TerrainPSInput input) : SV_TARGET
{
    float2 uv = input.uv * 20.0;

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
    float slopeBlend = smoothstep(0.7, 1.0, Nw.y);
    float heightBlend = smoothstep(-0.015, 0.25, input.worldPosition.y);

    float3 albedo = lerp(rockCol, lerp(grassCol, snowCol, heightBlend), slopeBlend);
    float3 blendedN = lerp(rockN, lerp(grassN, snowN, heightBlend), slopeBlend);
    float3 blendedM = lerp(rockM, lerp(grassM, snowM, heightBlend), slopeBlend);

    blendedN = blendedN * 2.0 - 1.0;
    blendedN.z = sqrt(1.0 - saturate(dot(blendedN.xy, blendedN.xy)));
    blendedN = normalize(blendedN);

    float3 T = normalize(input.tangent);
    float3 B = normalize(input.binormal);
    float3x3 TBN = float3x3(T, B, Nw);
    float3 N = normalize(mul(blendedN, TBN));

    float ao = blendedM.r;
    float roughness = blendedM.g;
    float metalness = blendedM.b;

    float3 toEye = normalize(cameraPos - input.worldPosition.xyz);

#if DEBUG_MODE == 1
    float3 diffuseColor = 1.0;

    float NdL = saturate(dot(N, normalize(-dirLightDir)));

    float3 direct =
        diffuseColor *
        NdL *
        dirLightColor *
        dirLightIntensity;

    return float4(tonemap_s_gamut3_cine(direct), 1.0);
    
#elif DEBUG_MODE == 2
    float3 diffuseColor = (float3)0.0;
    float3 specularColor = lerp((float3)0.04, albedo, metalness);

    // float3 ambiance = EvaluateAmbiance(environmentTexture, N, Nw,
    //     toEye, roughness, ao, diffuseColor, specularColor);

    float3 direct = EvaluateDirectionalLight(diffuseColor, specularColor, N, roughness,
        dirLightColor * dirLightIntensity, normalize(-dirLightDir), toEye);

    float3 radiance = direct;
    return float4(tonemap_s_gamut3_cine(radiance), 1.0);

#else
    float3 specularColor = lerp((float3)0.04, albedo, metalness);
    float3 diffuseColor = lerp((float3)0.05, albedo, 1.0 - metalness);
float clampedRoughness = max(roughness, 0.95); 

    float3 ambiance = EvaluateAmbiance(environmentTexture, N, Nw,
        toEye, clampedRoughness, ao, diffuseColor, specularColor);

    float3 direct = EvaluateDirectionalLight(diffuseColor, specularColor, N, roughness,
        dirLightColor * dirLightIntensity, normalize(-dirLightDir), toEye);

    float3 radiance = ambiance + direct;
    return float4(tonemap_s_gamut3_cine(radiance), 1.0);
#endif
}