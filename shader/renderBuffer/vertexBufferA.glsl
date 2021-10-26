#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

uniform mat4		model;
uniform mat4		projection;
uniform mat4		view;
out vec3 position;

vec3    rotateX(vec3 p, float theta)
{
    mat3    mat = mat3(vec3(1., 0., 0.),
	vec3(0., cos(theta), -sin(theta)),
	vec3(0., sin(theta), cos(theta)));
			
    return (mat * p);
}

void main()
{
	position = (projection * model * vec4(rotateX(aPos, radians(-90.)) * 0.1, 1.0)).xyz;
	gl_Position = projection *  model * vec4(rotateX(aPos, radians(-90.)) * 0.1, 1.0);
}