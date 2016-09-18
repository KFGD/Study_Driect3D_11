struct PIXEL_IN
{
	float4 position : SV_Position;
	float3 diffuse : COLOR;
};
float4 main(PIXEL_IN input) : SV_TARGET
{
	return float4(saturate(input.diffuse), 1);
}