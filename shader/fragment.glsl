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

#define AMBIENT_COEF 0.1 
#define LIGHT_COL vec3(1.0, 1.0, 1.0)

void	main()
{
	vec3	ambient = AMBIENT_COEF * LIGHT_COL;
	vec3	lightDir = normalize(u_lightPos - pos.xyz);
	float	diff = max(dot(lightDir, norm), 0.0);
	vec3	diffuse = diff * LIGHT_COL;

	if (isText == 1)
	{
		vec4	textColor = texture(text, textureCoord);
		FragColor = vec4(ambient + diffuse, 1.) * textColor;
	}
	else
		FragColor = vec4((ambient + diffuse) * colorMat, 1.);
}
