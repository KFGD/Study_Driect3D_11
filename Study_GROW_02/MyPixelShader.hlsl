struct PIXEL_IN {
	float4 pos : SV_POSITION;
};

cbuffer MyConstantBuffer : register (b0)
{
	float4 mColor;
};


float4 main(PIXEL_IN inp) : SV_TARGET
{
	return mColor;
}