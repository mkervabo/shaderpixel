#version 410 core

out vec4	FragColor;
in	vec4	color;
in	vec2	textureCoord;
in	vec3	norm;

uniform sampler2D	text;
uniform vec3		colorMat;
uniform int			isText;

void	main()
{
	if (isText == 1)
	{
		vec4	textColor = texture(text, textureCoord);
		FragColor = textColor;
	}
	else
		FragColor = vec4(colorMat, 1.);
}
