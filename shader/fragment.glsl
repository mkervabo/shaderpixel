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
uniform vec3		eye;

uniform float		K_S;
// uniform float		K_D;

#define AMBIENT_COEF 0.1 
#define LIGHT_COL vec3(1.0, 1.0, 1.0)

#define K_SHIN 10.;

void	main()
{
	vec3	ambient = AMBIENT_COEF * LIGHT_COL;
	vec3	lightDir = normalize(u_lightPos - pos.xyz);
	vec3	vPToEye = normalize(eye - pos.xyz);
	float	diff = max(dot(lightDir, norm), 0.0);

	vec3 rL = reflect(lightDir, norm);
	float spec = max(dot(-rL, vPToEye), 0.);

	// if (diffuse < EPSILON)
	// 	return (vec3(0., 0., 0.));
	// if (specular < EPSILON)
	// 	return (light.intensity * (colorObj * diffuse * K_D));

	vec3	diffuse = LIGHT_COL * diff * 1.;
	vec3	specular = LIGHT_COL * pow(spec, K_S) * 0.;

	if (isText == 1)
	{
		vec4	textColor = texture(text, textureCoord);
		FragColor = vec4(clamp(ambient + diffuse + specular, 0., 1.), 1.) * textColor;
	}
	else
		FragColor = vec4(clamp(ambient + diffuse + specular, 0., 1.) * colorMat, 1.);
}
