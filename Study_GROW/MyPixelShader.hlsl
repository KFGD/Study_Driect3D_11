struct PIXEL_IN {
	float4 pos : SV_POSITION;
};

float4 main(PIXEL_IN inp) : SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	return float4(0.0f, 0.0f, 0.0f, 1.0f);
}