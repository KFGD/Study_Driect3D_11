struct VERTEX_IN {
	float3 pos : POSITION;
};

struct PIXEL_IN {
	float4 pos : SV_POSITION;
};

cbuffer MyConstantBuffer : register (b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

PIXEL_IN main(VERTEX_IN inp) {
	PIXEL_IN ret;
	ret.pos = float4(inp.pos, 1);	//0은 변위(Vector), 1은 위치(Point)
	ret.pos = mul(ret.pos, world);
	ret.pos = mul(ret.pos, view);
	ret.pos = mul(ret.pos, proj);
	return ret;
}