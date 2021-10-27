#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

uniform mat4		model;
uniform mat4		view;
uniform mat4		projection;
out vec4			pos;

void main()
{
	pos = model * vec4(aPos * 2.5, 1.0);
	gl_Position = projection * view * pos;
}