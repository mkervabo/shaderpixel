#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

uniform mat4		model;

out vec2			tCoords;

void main()
{
	tCoords = aTex;
	gl_Position = model * vec4(aPos, 1.);
}