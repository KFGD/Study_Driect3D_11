struct PIXEL_IN
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD;
};

Texture2D colorRenderTarget : register(t0);
Texture2D positionRenderTarget : register(t1);
Texture2D normalRenderTarget : register(t2);
Texture2D depthStencil : register(t3);
SamplerState samplerState
{
    Filter = MIN_MAG_MIP_Point;
    AddressU = Clamp;
    AddressV = Clamp;
};

cbuffer Lights : register(b0)
{
    float4 light[8];
};

float4 main(PIXEL_IN inp) : SV_TARGET
{
    float4 colorRTsample = colorRenderTarget.Sample(samplerState, inp.texcoord);
    float4 positionRTsample = positionRenderTarget.Sample(samplerState, inp.texcoord);
    float4 normalRTsample = normalRenderTarget.Sample(samplerState, inp.texcoord);
    float depthStencilSample = depthStencil.Sample(samplerState, inp.texcoord).r;

    float4 r = { 0, 0, 0, 0 };
    for (int i = 0; i < 8; ++i)
    {
        if(light[i].w)
        {
            float3 lightDir = positionRTsample.xyz - light[i].xyz;
            float3 nLightDir = normalize(lightDir);
            float3 calced = saturate((float3) dot(-nLightDir, normalRTsample.xyz));
            r += float4(calced / (length(lightDir) / light[i].w), 1) * colorRTsample;
        }
    }
    return r;
}