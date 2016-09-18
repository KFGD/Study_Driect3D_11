#pragma pack_matrix(row_major)

struct VERTEX_IN
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct VERTEX_OUT
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

VERTEX_OUT main( VERTEX_IN input )
{
    VERTEX_OUT ret;
    ret.position = float4(input.position, 1);
    ret.color = input.color;
    return ret;
}