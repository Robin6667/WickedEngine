#include "globals.hlsli"

struct VertexToPixel {
	float4 pos	: SV_POSITION;
	centroid float4 col	: COLOR;
};

VertexToPixel main( float4 inPos : POSITION, float4 inCol : TEXCOORD0 )
{
	VertexToPixel Out = (VertexToPixel)0;
	Out.pos = mul( inPos, g_xTransform);
	Out.col = inCol * g_xColor;

	return Out;
}