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


 vec3    rotateY(vec3 p, float theta)
{
    mat3    mat = mat3(vec3(cos(theta), 0., sin(theta)),
			vec3(0., 1., 0.),
			vec3(-sin(theta), 0., cos(theta)));
			
    return (mat * p);
}

void main()
{
	textureCoord = aTex;
	norm = aNorm;
	pos = model * vec4(aPos, 1.);
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}
