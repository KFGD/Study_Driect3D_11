struct PIXEL_IN
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD;
};

#define BlurSizeH   1.0 / 1280.0
#define BlurSizeV   1.0 / 720.0

Texture2D mySampler;
SamplerState samplerState;

float4 main(PIXEL_IN input) : SV_TARGET
{
    float4 sum = float4(0, 0, 0, 0);
    for (int x = -4; x<=4; ++x)
        for (int y = -4; y<=4; ++y)
            sum += mySampler.Sample(samplerState, input.texcoord + float2(x * BlurSizeH, y * BlurSizeV))/81.0;

    return sum;

}