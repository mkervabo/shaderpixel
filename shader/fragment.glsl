#version 410 core

out vec4	FragColor;
in	vec4	color;
in	vec2	textureCoord;

uniform sampler2D text;

void	main()
{
	// vec3	alphaC = vec3(0.9, 0.9, 0.9);
	vec4	textColor = texture(text, textureCoord);
	// if (textColor.r > alphaC.r && textColor.g > alphaC.g && textColor.b > alphaC.b)
	// 	FragColor = vec4(0., 0., 0., 0.);
	// else
	FragColor = textColor;
}
