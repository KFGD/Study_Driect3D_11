struct PIXEL_IN
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

float4 main(PIXEL_IN input) : SV_TARGET
{
    return input.color;
}