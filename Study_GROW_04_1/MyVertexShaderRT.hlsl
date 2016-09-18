struct VERTEX_IN
{
    float3 position : POSITION;
    float2 texcoord : TEXCOORD;
};

cbuffer MyConstantBuffer : register(b0)
{
    float4x4 world;
    float4x4 proj;
};

struct VERTEX_OUT
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD;
};

VERTEX_OUT main(VERTEX_IN input)
{
    VERTEX_OUT ret;
    ret.position = float4(input.position, 1);
    //Homework
    ret.position = mul(ret.position, world);
    ret.position = mul(ret.position, proj);
    //~Homework
    ret.texcoord = input.texcoord;
    return ret;
}