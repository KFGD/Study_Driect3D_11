StructuredBuffer<float> bufferIn : register(t0);
RWStructuredBuffer<float> bufferOut : register(u0);

[numthreads(512, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID )
{
    bufferOut[DTid.x] = sqrt(bufferIn[DTid.x]);
}