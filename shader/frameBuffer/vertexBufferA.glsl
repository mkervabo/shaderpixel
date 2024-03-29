#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out vec2			tCoords;

vec3    rotateX(vec3 p, float theta)
{
    mat3    mat = mat3(vec3(1., 0., 0.),
	vec3(0., cos(theta), -sin(theta)),
	vec3(0., sin(theta), cos(theta)));
			
    return (mat * p);
}

void main()
{
	tCoords = aTex;
	gl_Position = vec4(rotateX(aPos, -1.5708), 1.);
}