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

cbuffer MyConstantBuffer : register(b0)
{
    float4x4 world : WORLD;
    float4x4 view : VIEW;
    float4x4 proj : PROJECTION;
};

VERTEX_OUT main( VERTEX_IN input )
{
    VERTEX_OUT ret;
    ret.position = float4(input.position, 1);
    ret.position = mul(ret.position, world);
    ret.position = mul(ret.position, view);
    ret.position = mul(ret.position, proj);
    ret.texcoord = input.texcoord;
    return ret;
}