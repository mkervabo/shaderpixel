#version 410 core

out vec4		fragColor;
in vec2			tCoords;

uniform vec2	u_resolution;
uniform float	time;


const mat2 coef = mat2(0.80,  0.60, -0.60,  0.60);

vec2 hash(vec2 p) {
	vec3 p3 = fract(vec3(p.xyx) * 0.23);
	p3 += dot(p3, p3.zyx + 19.19);
	return fract((p3.yx + p3.xz) * p3.zy);
}

float noise(in vec2 p)
{
	const float k1 = 0.36;
	const float k2 = 0.21;
	vec2 i = floor(p + (p.x + p.y) * k1);	
	vec2 a = p - i + (i.x + i.y) * k2;
	vec2 o = (a.x > a.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
	vec2 b = a - o + k2;
	vec2 c = a - 1.0 + 2.0 * k2;
	vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c) ), 0.0 );
	vec3 n = h * h * h * h * vec3( dot(a, hash(i + 0.0)), dot(b,hash(i + o)), dot(c, hash(i + 1.0)));
	return dot(n, vec3(70.0));	
}

float fbm1(vec2 p)
{
	float f = 0.0;
	f += 0.9000 * noise(p);
	p = coef * p * 2.;
	f += 0.2000 * noise(p);
	p = coef * p * 1.;
	f += 0.1000 * noise(p);
	p = coef * p;
	return (f / 0.9);
}

float fbm2(vec2 p)
{
	float f = 0.0;
	f += 0.3 * (0.5 + 0.5 * noise(p));
	p = coef * p * 2.02;
	f += 0.1 * (0.5 + 0.5 * noise(p));
	p = coef * p * 1.02;
	f += 0.08 * (0.5 + 0.5 * noise(p));
	p = coef* p * .02;
	return (f / 0.9);
}

vec2 fbm1Vec2(vec2 p)
{
	return vec2(fbm1(p), fbm1(p + vec2(6.)));
}

vec2 fbm2Vec2(vec2 p)
{
	return vec2(fbm2(p + vec2(10.8)), fbm2(p + vec2(.5)));
}

float fbms(vec2 p)
{
	p += 0.02 * sin(vec2(0.6) * time + length(p));
	vec2 o = fbm1Vec2(0.9 * p);
	o += 0.04 * sin(vec2(0.12) * time + length(o));
	vec2 n = fbm2Vec2(3.0 * o);
	float f = 0.3 + 0.3 * fbm1(1.8 * p + 7.0 * n);
	return f;
}


void main()
{
	vec2 p = tCoords;

	float e = 1.0 / u_resolution.y;
	float f = fbms(p);
	vec3 col = vec3(0.5);
	vec3 nor = normalize(vec3(
		fbms(p + vec2(e, 0.0)) - f, 2.0 * e, fbms(p + vec2(0.0, e)) - f)
	);
	vec3 lig = normalize(vec3(0.5));
	float dif = clamp(10. * dot(nor, lig), 0.0, 1.0);
	vec3 lin = vec3(0.6) * (nor.y * 0.6 + 0.6) + vec3(0.3) * dif;
	col *= 1.6 * lin;
	col = 1.0 - col;

	fragColor = vec4(col, 1.0);
}
