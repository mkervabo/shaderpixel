#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

uniform mat4		model;
uniform mat4		projection;

out	vec4	color;
out	vec2	textureCoord;
out	vec3	norm;
out	vec4	pos;

void main()
{
	textureCoord = aTex;
	pos = model * vec4(aPos, 1.);
	norm = aNorm;
	gl_Position = projection * model * vec4(aPos, 1.0);
}