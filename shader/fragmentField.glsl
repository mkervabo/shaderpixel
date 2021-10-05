#version 410 core

in vec4			pos;
out vec4		FragColor;

uniform mat4	modelMat;
uniform mat4	view;
uniform vec3	eye;
uniform float	time;

uniform mat4	inverseView;
uniform mat4	projection;
uniform float	farNear[2];
uniform float	u_fov;
uniform vec2	u_resolution;
uniform vec3	u_lightPos;

const int MAX_STEPS = 200;
const int MAX_AO_STEPS = 10;
const float MIN_DIST = 0.0;
const float MAX_DIST = 10.;
const float EPSILON = 0.002;

#define K_A 0.2
#define K_SHIN 10.
#define K_S 0.1
#define K_D 0.8

#define sat(x) clamp(x, 0., 1.)

struct s_light
{
	vec3 pos;
	vec3 colorLight;
	float intensity;
};

float smin( float a, float b, float k )
{
	float h = max(k-abs(a-b),0.0);
	return min(a, b) - h*h*0.25/k;
}

float smax( float a, float b, float k )
{
	float h = max(k-abs(a-b),0.0);
	return max(a, b) + h*h*0.25/k;
}

float random (in vec2 p) {
	vec3 p3  = fract(vec3(p.xyx) * .1031);
	p3 += dot(p3, p3.yzx + 33.33);
	return fract((p3.x + p3.y) * p3.z);
}

float noise (in vec2 st) {
	vec2 i = floor(st);
	vec2 f = fract(st);

	// Four corners in 2D of a tile
	float a = random(i);
	float b = random(i + vec2(1.0, 0.0));
	float c = random(i + vec2(0.0, 1.0));
	float d = random(i + vec2(1.0, 1.0));

	vec2 u = f * f * (3.0 - 2.0 * f);

	return mix(a, b, u.x) +
			(c - a)* u.y * (1.0 - u.x) +
			(d - b) * u.x * u.y;
}

#define OCTAVES 128.
float fbm (in vec2 st, float octaves)
{
	float value = 0.;
		
	for (float i = 1.; i < octaves; i += i)
		value += noise(st * i) / i;
	return value;
}

vec4 unionSDF(vec4 a, vec4 b)
{
	return (a.w < b.w ? a : b);
}

float sphereDE(vec3 p, float rayon)
{
	return (length(p) - rayon);
}

float DistanceEstimation(vec3 p, float octaves)
{
	float terrain = fbm(p.xz, octaves) * 0.3; // 5 * 0.3 => 1.5
	terrain = 0.4 * (p.y + terrain * 2.5 - 1.5);// (p.y - 1.) * 0.8
	return (terrain);
}

float ShortestDistanceToSurface(vec3 eyeP, vec3 marchinDir, float start,
	float end, float octaves)
{
	float depth = start;
	float dist;
	for (int i = 0; i < MAX_STEPS; i++)
	{
		dist = DistanceEstimation(eyeP + marchinDir * depth, octaves);
		if (dist < EPSILON)
			return (depth);
		depth += dist;
		if (depth > end ||
			(depth > end - EPSILON && depth < end + EPSILON))
			return end;
	}
	return (end);
}

vec3 calculateMarchinDir(float fov, vec2 resolutionSize, vec2 fragCoord)
{
	float	ratio = resolutionSize.x / resolutionSize.y;
	vec2	xy = (fragCoord - 0.5) / resolutionSize;
	//from [0,1] to [-1, 1]
	xy.x = (2 * xy.x - 1) * ratio * tan(radians(fov / 2.));
	xy.y = (2 * xy.y - 1) * tan(radians(fov / 2.));
	return (normalize(vec3(xy, -1)));
}

vec3 estimateNormal(vec3 p, float octaves)
{
	return (normalize(vec3(DistanceEstimation(vec3(p.x + EPSILON, p.y, p.z), octaves)
		- DistanceEstimation(vec3(p.x - EPSILON, p.y, p.z), octaves),
			DistanceEstimation(vec3(p.x, p.y + EPSILON, p.z), octaves)
		- DistanceEstimation(vec3(p.x, p.y - EPSILON, p.z), octaves),
			DistanceEstimation(vec3(p.x, p.y, p.z + EPSILON), octaves)
		- DistanceEstimation(vec3(p.x, p.y, p.z - EPSILON), octaves))));
}

vec3 phongLight(s_light light, vec3 vPToEye, vec3 norm, vec3 pos, vec3 colorObj)
{
	vec3 vPL = normalize(light.pos - pos);
	float diffuse = dot(vPL, norm) * K_D;

	vec3 reflL = reflect(vPL, norm);
	float specular = dot(-reflL, vPToEye);

	if (diffuse < EPSILON)
		return (vec3(0., 0., 0.));
	if (specular < EPSILON)
	{
		return (light.intensity * (colorObj * diffuse));
	}
	vec3 ret = vec3(0.);

	ret = light.intensity * (colorObj * diffuse);
	ret += light.intensity * (light.colorLight * pow(specular, K_SHIN) * K_S);
	return (ret);
}


mat4 viewMatrix(vec3 eye, vec3 pToLook, vec3 up)
{
	vec3 front = normalize(pToLook - eye);
	vec3 right = normalize(cross(front, up));
	vec3 newUp = normalize(cross(right, front));
	return (mat4(
		vec4(right, 0.),
		vec4(newUp, 0.),
		vec4(-front, 0.),
		vec4(vec3(0.0), 1.0)
	));
}

vec3 calculateColor(s_light light, vec3 eye, vec3 norm, vec3 pos, float dist, vec3 skyColor)
{
	// return (vec3(pos.y));
	
	float posY = pos.y;

	vec3 color = vec3(0.);// = vec3(1., 0., 1.);
	vec3 vPToEye = normalize(eye - pos);

	vec3 rockColor = vec3(158. / 255., 100. / 255., 48. / 255.) / 2.;
	vec3 forestColor = vec3(0.3, 0.42, 0.3);
	color = mix(forestColor, rockColor, smoothstep(0.3, 0.8, posY));
	// color += mix(vec3(0.3, 0.42, 0.3), rockColor, smoothstep(-100., 200., posY));
	
	// float smoothSnow = smoothstep(100., 500., posY);
	float smoothSnow = smoothstep(0.9, 1., posY);
	color += smoothSnow * vec3(1.);
	
	color = phongLight(light, vPToEye, norm, pos, color);
	color = mix(color, skyColor, smoothstep(-4., 8., dist));
	return (color);
}

void main(void)
{
	vec3 dir = calculateMarchinDir(u_fov, u_resolution, gl_FragCoord.xy / 2.);
	
	//vec3 eyeP = eye + vec3(0., 2., 0.5);
	//float moove = time * 0.5;
	float moove = 0.;
	vec3 eyeP = eye + vec3(0., 1.5, moove);

	vec3 worldDir = (inverseView * vec4(dir, 0.0)).xyz;

	vec3 skyColor = mix(vec3(.7, .8, 1.), vec3(0.1, 0.1, .2), sat(worldDir.y + 0.5));

	float dist = ShortestDistanceToSurface(eyeP, worldDir, MIN_DIST, MAX_DIST, 128.);
	vec3 posHit = eyeP + worldDir * dist;
	float octaves;

	if (dist < 4.)
		octaves = 128.; // 128
	else if (dist < 8.)
		octaves = 64.; // 64
	else
		octaves = 8.; // 8
	
	vec3 norm = estimateNormal(posHit, octaves);

	if (dist > MAX_DIST - EPSILON)
	{
		FragColor = vec4(skyColor, 0.98);
		return ;
	}
	s_light light;
	// light.pos = eye;
	light.pos = vec3(0., 10., 0.);
	// light.pos = vec3(u_lightPos);
	//light.pos.z += moove;
	light.colorLight = vec3(1.0, 1.0, 1.0);
	light.intensity = 0.5;

	float distToObj = distance(pos.xyz, eye);
	dist = distToObj < 0. ? dist : dist - distToObj;
	vec3 color = calculateColor(light, eyeP, norm, posHit, dist, skyColor);
	FragColor = vec4(color, 1.0);
}