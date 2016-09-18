#pragma pack_matrix(row_major)

struct VERTEX_IN
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct VERTEX_OUT
{
    float4 position : SV_Position;
    float3 diffuse : COLOR;
};

cbuffer MyConstantBuffer : register(b0)
{
    float4x4 world : WORLD;
    float4x4 view : VFACE;
    float4x4 proj : PROJECTION;
    float4 pointLightPosition;
};

VERTEX_OUT main( VERTEX_IN input )
{
    VERTEX_OUT ret;
    ret.position = float4(input.position, 1);
    ret.position = mul(ret.position, world);

    float3 lightDir = normalize(ret.position.xyz - pointLightPosition.xyz);

    ret.position = mul(ret.position, view);
    ret.position = mul(ret.position, proj);

    float3 worldNormal = normalize(mul(-input.normal, (float3x3) world));
    ret.diffuse = dot(lightDir, worldNormal);

    return ret;
}