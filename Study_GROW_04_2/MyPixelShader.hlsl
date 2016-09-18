struct PIXEL_IN
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD;
};

Texture2D mySampler;
SamplerState samplerState;

float4 main(PIXEL_IN input) : SV_TARGET
{
    return mySampler.Sample(samplerState, input.texcoord) * float4(1, 1, 1, 0.5f);
}