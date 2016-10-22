#version 300 es

uniform mat4 projection, modelview;

in lowp vec2 position;
in lowp vec2 texCoord;
out lowp vec2 texCoordFrag;

void main()
{
	// Pass texture coordinates
	texCoordFrag = texCoord;
	// Transform position from pixel coordinates to clipping coordinates
	gl_Position = projection * modelview * vec4(position, 0.0, 1.0);
}

