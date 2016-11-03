#version 120

uniform mat4 projection, modelview;

attribute vec2 position;

void main()
{
	// Transform position from pixel coordinates to clipping coordinates
	gl_Position = projection * modelview * vec4(position, 0.0, 1.0);
}
