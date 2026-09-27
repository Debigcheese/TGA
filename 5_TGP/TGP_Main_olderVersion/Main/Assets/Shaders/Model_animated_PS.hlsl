#include "common.hlsli"

struct PSIn
{
    float4 position : SV_POSITION;
    float4 worldPos : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float3 worldNormal : NORMAL;
};

float4 main(PSIn i) : SV_TARGET
{
    float3 N = normalize(i.worldNormal);

    float upFac = N.y * 0.5 + 0.5;
    float3 ambient = lerp(ambientGround, ambientSky, upFac);

    float3 lightDir = normalize(-dirLightDir);
    float3 diffuse = dirLightColor * saturate(dot(N, lightDir));

    float4 texCol = albedoTexture.Sample(defaultSampler, i.uv);

    float3 emissive = float3(
        sin(totalTime * 1.0) * 0.5 + 0.5,
        sin(totalTime * 1.3 + 2.094) * 0.5 + 0.5,
        sin(totalTime * 1.7 + 4.189) * 0.5 + 0.5
    ) * 0.3;

    float3 finalColor = texCol.rgb * i.color.rgb * (ambient + diffuse) + emissive;

    return float4(finalColor, texCol.a);
}