#version 410 core

out vec4	FragColor;
in	vec2	textureCoord;
in	vec3	norm;
in	vec4	pos;

uniform sampler2D	text;
uniform vec3		colorMat;
uniform int			isText;
uniform vec3		eye;

uniform float		K_S;

#define AMBIENT_COEF 0.1 
#define LIGHT_COL vec3(1.0, 1.0, 1.0)

#define K_SHIN 10.;
#define DISTANCE 20.

mat3	rotateX(float theta)
{
	return (mat3(vec3(1., 0., 0.),
	vec3(0., cos(theta), -sin(theta)),
	vec3(0., sin(theta), cos(theta))));
}

void	main()
{
	float	dist = 0.;
	vec3	lightDir = vec3(0.);
	vec3	vPToEye = normalize(eye - pos.xyz);
	vec3	ambient = AMBIENT_COEF * LIGHT_COL;
	float	diff = 0.;
	float	spec = 0.;
	vec3	rL = vec3(0.);
	mat3	rotX = rotateX(-90.);
	vec3	lightPos = rotX * vec3(3., 3., 5.);

	dist = 1. - min(distance(lightPos, pos.xyz), DISTANCE) / DISTANCE;
	lightDir = normalize(lightPos - pos.xyz);
	diff += max(dot(lightDir, norm), 0.0) * dist;
	rL = reflect(lightDir, norm);
	spec += max(dot(-rL, vPToEye), 0.) * dist;

	vec3	diffuse = LIGHT_COL * min(diff, 1.) * 1.;
	vec3	specular = LIGHT_COL * pow(min(spec, 1.), K_S) * 0.;

	if (isText == 1)
	{
		vec4	textColor = texture(text, textureCoord);
		FragColor = vec4(clamp(ambient + diffuse + specular, 0., 1.), 1.) * textColor;
	}
	else
		FragColor = vec4(clamp(ambient + diffuse + specular, 0., 1.) * colorMat, 1.);
}
