#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out vec2 textureCoord;
out vec3 norm;
out vec4 pos;

uniform mat4		model;
uniform mat4		view;
uniform mat4		projection;


void main()
{
	textureCoord = aTex;
	norm = aNorm;
	pos = vec4(aPos, 1.);
	gl_Position = projection * view * model * vec4(aPos / 8., 1.0);
}
