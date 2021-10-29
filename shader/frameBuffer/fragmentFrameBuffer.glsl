#version 410 core

out vec4 fragColor;

uniform sampler2D bufferA;
uniform sampler2D img;

float waterStrength = 0.8;
float waterDye = 0.5;
float sin120 = 0.66;

in vec2 tCoords;

void main()
{
	vec2 px = vec2(0.003),
	uv = tCoords,
	time = vec2(0., 0.1),
	uvtime = uv + time;

	//compute water normal, depth, height, light and distorsion
	vec3 p1 = vec3(uv, texture(bufferA, uv).r);
	uv.x += px.x;
	vec3 p2 = vec3(uv, texture(bufferA, uv).r);
	uv.x -= px.x;
	uv.y += px.y;
	vec3 p3 = vec3(uv, texture(bufferA, uv).r);
	uv.y -= px.y;
	float waterHeight = p1.z,
	depth = clamp(waterHeight, 0., 1.);
	vec3 norm = cross(p2 - p1, p3 - p1);
	norm.z *= 40. / waterStrength;
	float reflection = smoothstep(
		0.99, 1.0, refract(-normalize(norm), 
		normalize(vec3(uv - vec2(0.5,0.5), -1.)), 0.6).z
	);
	norm.z *= ((1. - depth) * 50.) / waterStrength;
	norm = normalize(norm);  
	vec2 displacement = norm.xy * float(waterHeight);

	//compute rock height map, normal, light 
	vec3 rockHeight = vec3(uv, texture(img, uvtime + displacement).r);
	uv.y += px.y;
	p1 = vec3(uv, texture(img, uv + time + displacement).r);
	p2 = vec3(uv, texture(img, uv + time + displacement).r); 
	uv.x -= px.x * sin120 * 2.;
	p3 = vec3(uv, texture(img, uv + time + displacement).r);
	vec3 rockNorm = normalize(cross(p2-p1, p3-p1) * vec3(1., 0.5, 1.));
	vec3 norm1 = normalize(cross(p1 - rockHeight, p1 - rockHeight));
	float rockDiffuse = 0.3 + clamp(reflect(rockNorm, normalize(vec3(uv -  vec2(0.5,0.5), -1.))).z, -.1, 1.),
	lightPow = 1.5 - distance(uv,  vec2(0.5, 0.5));
	vec2 smp = uvtime + rockNorm.xy * 0.03;

	//draw
	fragColor = vec4(vec3(0.7), 1);
	vec3 color = vec3(waterDye - 0.1, waterDye + 0.2, waterDye + 0.4);
	float ambiante = 0.3 - p1.z;
	fragColor.rgb *= (color + ambiante);
}
