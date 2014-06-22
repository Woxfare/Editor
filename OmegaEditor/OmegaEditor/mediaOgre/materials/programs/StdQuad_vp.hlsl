void StdQuad_vp
(
    in float4 inPos : POSITION,

    out float4 pos : POSITION,
    out float2 uv0 : TEXCOORD0,

    uniform float4x4 worldViewProj
)
{
    // Use standardise transform, so work accord with render system specific (RS depth, requires texture flipping, etc)
    pos = mul(worldViewProj, inPos);

    // The input positions adjusted by texel offsets, so clean up inaccuracies
    inPos.xy = sign(inPos.xy);

    // Convert to image-space
    uv0 = (float2(inPos.x, -inPos.y) + 1.0f) * 0.5f;
}

