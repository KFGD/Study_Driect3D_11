#pragma pack_matrix(row_major)

struct VERTEX_IN
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct VERTEX_OUT
{
    float4 position : SV_Position;
    float4 real_position : POSITION;
    float3 normal : NORMAL;
};

cbuffer BunnyTransform : register(b0)
{
    float4x4 world : WORLD;
    float4x4 view : VFACE;
    float4x4 proj : PROJECTION;
};

VERTEX_OUT main(VERTEX_IN input)
{
    VERTEX_OUT ret;
    ret.position = float4(input.position, 1);
    ret.position = mul(ret.position, world);
    ret.real_position = ret.position;
    ret.position = mul(ret.position, view);
    ret.position = mul(ret.position, proj);
    ret.normal = mul(input.normal, (float3x3) world);
    return ret;
}