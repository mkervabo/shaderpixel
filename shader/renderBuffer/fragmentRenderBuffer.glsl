#version 410 core

out vec4 fragColor;

uniform vec2	u_resolution;
uniform float	u_fov;
uniform mat4	projection;
uniform mat4	view;
uniform vec3	eye;
uniform mat4	inverseView;
uniform float	farNear[2];

uniform sampler2D	bufferA;

in vec2 tCoords;

void main()
{
	fragColor = texture(bufferA, tCoords);
}