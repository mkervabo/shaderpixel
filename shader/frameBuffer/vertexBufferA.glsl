#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

uniform mat4		model;

out vec2			tCoords;

mat3	rotateX(float theta)
{
	return mat3(vec3(1., 0., 0.),
			vec3(0., cos(theta), -sin(theta)),
			vec3(0., sin(theta), cos(theta)));
}

void main()
{
	tCoords = aTex;
	gl_Position = vec4(rotateX(radians(90.)) * aPos, 1.);
}