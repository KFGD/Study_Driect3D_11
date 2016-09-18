struct VERTEX_IN {
	float3 pos : POSITION;
};

struct PIXEL_IN {
	float4 pos : SV_POSITION;
};

PIXEL_IN main(VERTEX_IN inp) {
	PIXEL_IN ret;
	ret.pos = float4(inp.pos, 1);	//0은 변위(Vector), 1은 위치(Point)
	return ret;
}