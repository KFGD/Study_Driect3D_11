struct PIXEL_IN
{
    float4 position : SV_Position;
};

cbuffer Color
{
    float4 color;
};

float4 main(PIXEL_IN input) : SV_TARGET
{
    return color;
}