#version 120

uniform vec4 color;
uniform sampler2D tex;

varying vec2 texCoordFrag;
//out vec4 outColor;
uniform float isDamaged;

void main()
{
	// Discard fragment if texture sample has alpha < 0.5
	// otherwise compose the texture sample with the fragment's interpolated color
	vec4 texColor = texture2D(tex, texCoordFrag);
	if(texColor.a < 0.5f)
		discard;
	if (isDamaged == 1.0f) gl_FragColor = vec4(1,1,0,1);
	else gl_FragColor = color * texColor;
}

