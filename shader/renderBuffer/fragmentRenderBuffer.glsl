#version 410 core

out vec4 fragColor;

uniform sampler2D	bufferA;

in vec2 tCoords;

void main()
{
	fragColor = texture(bufferA, tCoords);
}