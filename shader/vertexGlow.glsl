#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out mat4	modelMat;

uniform mat4		model;
uniform mat4		view;
uniform mat4		projection;

vec3    rotateZ(vec3 p, float theta)
{
    mat3    mat = mat3(vec3(cos(theta), -sin(theta), 0.),
			vec3(sin(theta), cos(theta), 0.),
			vec3(0., 0., 1.));
    return (mat * p);
}

void main()
{
	gl_Position = projection * view * model * vec4(rotateZ(aPos, -1.5708) * 0.4, 1.0);
}