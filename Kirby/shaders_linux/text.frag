#version 300 es

uniform lowp vec4 color;
uniform sampler2D tex;
uniform lowp vec2 minTexCoord, maxTexCoord;

in lowp vec2 texCoordFrag;
out lowp vec4 outColor;

void main()
{
	// Use minTexCoord and maxTexCoord to determine the sample textures coordinates
	// inside the font texture atlas. Use that texel to determine transparency
	// combining it with the incoming color.
	lowp vec2 texCoord = texCoordFrag * (maxTexCoord - minTexCoord) + minTexCoord;
	outColor = color * vec4(1, 1, 1, texture(tex, texCoord).r);
}

