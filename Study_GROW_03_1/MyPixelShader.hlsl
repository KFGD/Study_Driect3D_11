struct PIXEL_IN
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD;
};


Texture2D mySampler;
SamplerState samplerState;

float4 main( PIXEL_IN input ) : SV_TARGET
{
    float4 sample = mySampler.Sample(samplerState, input.texcoord);
    float3 mask = { 1, 1, 1 };
    sample.rgb = mask - sample.rgb;
    return sample;
}