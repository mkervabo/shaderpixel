#version 410 core

out vec4	FragColor;
in	vec4	color;
in	vec2	textureCoord;
in	vec3	norm;
in	vec4	pos;

uniform sampler2D	text;
uniform vec3		colorMat;
uniform int			isText;
uniform vec3		u_lightPos;

void	main()
{
	FragColor = vec4(1.);
}
