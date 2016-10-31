#version 120

uniform mat4 projection, modelview;
uniform vec2 texCoordDispl;

attribute vec2 position;
attribute vec2 texCoord;
varying vec2 texCoordFrag;

void main()
{
	// Pass texture coordinates to access a given texture atlas
	texCoordFrag = texCoord + texCoordDispl;
	// Transform position from pixel coordinates to clipping coordinates
	gl_Position = projection * modelview * vec4(position, 0.0, 1.0);
}

