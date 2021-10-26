#version 410 core

out vec4 fragColor;

uniform sampler2D	bufferA;
uniform float	time;
uniform vec2	u_resolution;

in vec2 tCoords;

void main()
{
	vec4 text = texture(bufferA, tCoords);
	fragColor =  vec4(text.xyz, 1.);
}