#version 300 es

uniform lowp vec4 color;
uniform lowp sampler2D tex;

in lowp vec2 texCoordFrag;
out lowp vec4 outColor;
uniform lowp float isDamaged;

void main()
{
	// Discard fragment if texture sample has alpha < 0.5
	// otherwise compose the texture sample with the fragment's interpolated color
	lowp vec4 texColor = texture(tex, texCoordFrag);
	if(texColor.a < 0.5f)
		discard;
	if (isDamaged == 1.0f) outColor = vec4(1,1,0,1);
	else outColor = color * texColor;
}

