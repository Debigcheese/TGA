#include "Deferred.hlsli"

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

GBufferOutput main(PSIn i)
{
    float4 texCol = albedoTexture.Sample(defaultSampler, i.uv);
    clip(texCol.a - 0.5f);

    float3 normalTS = normalTexture.Sample(defaultSampler, i.uv).xyz * 2.0f - 1.0f;
    float3 N = normalize(i.worldNormal);
    float3 T = i.worldTangent / max(length(i.worldTangent), 0.0001f);
    float3 B = i.worldBinormal / max(length(i.worldBinormal), 0.0001f);
    N = normalize(normalTS.x * T + normalTS.y * B + normalTS.z * N);

    GBufferOutput output;
    output.worldPosition = float4(i.worldPosition.xyz, 1.0f);
    output.albedo = float4(texCol.rgb * i.color.rgb, 1.0f);
    output.normal = float4(N * 0.5f + 0.5f, 1.0f);
    output.material = float4(materialTexture.Sample(defaultSampler, i.uv).rgb, 1.0f);
    return output;
}