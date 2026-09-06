#include "common.hlsli"

struct PSIn
{
    float4 position : SV_POSITION;
    float4 worldPosition : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float3 worldNormal : NORMAL;
};

float Attenuate(float dist, float range)
{
    float t = saturate(1.0f - dist / range);
    return t * t;
}

float3 Shade(float3 N, float3 V, float3 L, float3 lightColor)
{
    float NdotL = saturate(dot(N, L));
    float3 H = normalize(L + V);
    float spec = pow(saturate(dot(N, H)), 32.0f);
    return (NdotL + spec * 0.2f) * lightColor;
}

float4 main(PSIn i) : SV_TARGET
{
    if (emissiveStrength > 0.0f)
        return float4(emissiveColor * emissiveStrength, 1.0f);

    float3 N = normalize(i.worldNormal);
    float3 P = i.worldPosition.xyz;
    float3 V = normalize(cameraPos - P);

    float4 texCol = albedoTexture.Sample(defaultSampler, i.uv);
    float3 albedo = texCol.rgb * i.color.rgb;
    float3 result = 0.0f;

    if (isAdditivePass == 0)
    {
        float upFac = N.y * 0.5f + 0.5f;
        float3 ambient = lerp(ambientGround, ambientSky, upFac);

        float3 sunL = normalize(-dirLightDir);
        float3 diffuse = dirLightColor * dirLightIntensity * saturate(dot(N, sunL));

        result += albedo * (ambient + diffuse);
    }

    // point lights
    for (int p = 0; p < numPointLights; ++p)
    {
        float3 toLight = pointLights[p].position - P;
        float dist = length(toLight);
        float3 L = toLight / max(dist, 0.0001f);

        float att = Attenuate(dist, pointLights[p].range);
        result += albedo * Shade(N, V, L, pointLights[p].color * pointLights[p].intensity * att);
    }

    // spot lights
    for (int s = 0; s < numSpotLights; ++s)
    {
        float3 toLight = spotLights[s].position - P;
        float dist = length(toLight);
        float3 L = toLight / max(dist, 0.0001f);

        float att = Attenuate(dist, spotLights[s].range);

        // -L is the direction light travels, compare against the cone axis
        float cosAngle = dot(spotLights[s].direction, -L);
        float cone = smoothstep(spotLights[s].cosOuter, spotLights[s].cosInner, cosAngle);

        result += albedo * Shade(N, V, L, spotLights[s].color * spotLights[s].intensity * att * cone);
    }

    return float4(result, texCol.a);
}