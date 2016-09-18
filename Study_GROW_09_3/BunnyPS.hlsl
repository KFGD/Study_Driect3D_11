struct PIXEL_IN
{
    float4 position : SV_Position;
    float4 real_position : POSITION;
    float3 normal : NORMAL;
};

struct PIXEL_OUT
{
    float4 color : SV_Target0;
    float4 position : SV_Target1;
    float4 normal : SV_Target2;
};

PIXEL_OUT main(PIXEL_IN input)
{
    PIXEL_OUT ret;
    ret.color = float4(1, 1, 1, 1);
    ret.position = input.real_position;
    ret.normal = float4(normalize(input.normal), 1);
    return ret;
}