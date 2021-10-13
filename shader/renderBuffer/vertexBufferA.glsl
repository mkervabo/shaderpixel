#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

uniform mat4		inverseView;
uniform mat4		projection;
uniform mat4		view;

void main()
{
	gl_Position = projection * view * vec4(aPos, 0.5);
}