#include "common.hlsli"

struct PSIn
{
    float4 position : SV_POSITION;
    float4 worldPosition : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float3 worldNormal : NORMAL;
    float3 worldTangent : TANGENT;
    float3 worldBinormal : BINORMAL;
};

float Attenuate(float dist, float range)
{
    float t = saturate(1.0f - dist / range);
    return t * t;
}

float3 Shade(float3 N, float3 V, float3 L, float3 lightColor, float specStrength)
{
    float NdotL = saturate(dot(N, L));
    float3 H = normalize(L + V);
    float spec = pow(saturate(dot(N, H)), 32.0f);
    return (NdotL + spec * 0.2f * specStrength) * lightColor;
}

float4 main(PSIn i) : SV_TARGET
{
    if (emissiveStrength > 0.0f)
        return float4(emissiveColor * emissiveStrength, 1.0f);

    float3 normalTS = normalTexture.Sample(defaultSampler, i.uv).xyz * 2.0f - 1.0f;
    float3 N = normalize(i.worldNormal);
    float3 T = i.worldTangent / max(length(i.worldTangent), 0.0001f);
    float3 B = i.worldBinormal / max(length(i.worldBinormal), 0.0001f);
    N = normalize(normalTS.x * T + normalTS.y * B + normalTS.z * N);

    float3 P = i.worldPosition.xyz;
    float3 V = normalize(cameraPos - P);

    float4 texCol = albedoTexture.Sample(defaultSampler, i.uv);
    clip(texCol.a - 0.5f);
    float3 albedo = texCol.rgb * i.color.rgb;
    float specStrength = materialTexture.Sample(defaultSampler, i.uv).r;
    float3 result = 0.0f;

    if (isAdditivePass == 0)
    {
        float upFac = N.y * 0.5f + 0.5f;
        float3 ambient = lerp(ambientGround, ambientSky, upFac);

        float3 sunL = normalize(-dirLightDir);
        float3 diffuse = dirLightColor * dirLightIntensity * saturate(dot(N, sunL));

        result += albedo * (ambient + diffuse);
    }

    for (int p = 0; p < numPointLights; ++p)
    {
        float3 toLight = pointLights[p].position - P;
        float dist = length(toLight);
        float3 L = toLight / max(dist, 0.0001f);

        float att = Attenuate(dist, pointLights[p].range);
        result += albedo * Shade(N, V, L, pointLights[p].color * pointLights[p].intensity * att, specStrength);
    }

    for (int s = 0; s < numSpotLights; ++s)
    {
        float3 toLight = spotLights[s].position - P;
        float dist = length(toLight);
        float3 L = toLight / max(dist, 0.0001f);

        float att = Attenuate(dist, spotLights[s].range);

        float cosAngle = dot(spotLights[s].direction, -L);
        float cone = smoothstep(spotLights[s].cosOuter, spotLights[s].cosInner, cosAngle);

        result += albedo * Shade(N, V, L, spotLights[s].color * spotLights[s].intensity * att * cone, specStrength);
    }

    return float4(result, texCol.a);
}