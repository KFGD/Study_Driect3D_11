struct VERTEX_IN
{
    float3 position : POSITION;
    float2 texcoord : TEXCOORD;
};

struct VERTEX_OUT
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD;
};

VERTEX_OUT main ( VERTEX_IN input )
{
    VERTEX_OUT ret;
    ret.position = float4(input.position, 1);
    ret.texcoord = input.texcoord;
    return ret;
}