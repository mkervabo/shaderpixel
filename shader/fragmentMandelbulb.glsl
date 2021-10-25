#version 410 core

out vec4		FragColor;
in	vec2		textureCoord;
in	vec3		norm;

uniform mat4	modelMat;
uniform mat4	view;
uniform vec3	eye;
uniform vec3	modelPos;
uniform float	time;

uniform mat4	inverseView;
uniform mat4	projection;
uniform float	farNear[2];
uniform float	u_fov;
uniform vec2	u_resolution;
uniform vec3	u_lightPos;


const int MAX_ITERATIONS = 7; // 7
const int MAX_STEPS = 100; // 100
const int MAX_STEPS_REF = 10;
const int MAX_AO_STEPS = 5;
const int MAX_REFLECTIONS = 1;
const float EPSILON = 0.0025; // "/ SCALE"
const float EPSILON_REF = 0.01;
const float SCALE = 1.;

const vec3 COLOR_OBJ = vec3(0.8, 1., 1.);

#define K_A 0.4
#define K_S 10.
#define K_R 0.8
#define K_D 0.7

struct s_light
{
	vec3 pos;
	vec3 colorLight;
	float intensity;
};

float MandelbulbDE(vec3 pos, float power)
{
	vec3 z = pos;
	float dr = 1.0;
	float r = 0.0;
	float theta;
	float phi;
	for (int i = 0; i < MAX_ITERATIONS ; i++)
	{
		r = length(z);
		if (r > 2.)
			break;
		
		// convert to polar coordinates
		theta = asin(z.z / r);
		phi = atan(z.y / z.x);
		dr =  pow(r, power - 1.0) * power * dr + 1.0;
		
		// scale and rotate the point
		float zr = pow(r, power);
		theta *= power;
		phi *= power;
		
		// convert back to cartesian coordinates
		//z = zr * vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)); // real
		//z = zr * vec3(cos(theta) * cos(phi), cos(phi) * sin(theta), cos(theta)); // modify
		z = zr * vec3(cos(theta) * cos(phi), cos(theta) * sin(phi), sin(theta)); // symetry
		z += pos;
	}
	return (0.5 * log(r) * r / dr);
}

float boxDE(vec3 p, vec3 b)
{
	vec3 q = abs(p) - b;
	return (length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0));
}

float planSphereDE(vec3 z)
{
	z.xy = mod((z.xy),1.0)-vec3(0.5).xy;	// instance on xy-plane
	return length(z)-0.3;					// sphere DE
}

float sphereDE(vec3 p, float rayon)
{
	return (length(p) - rayon);
}

float DistanceEstimation(vec3 p)
{
	p -= modelPos;
	// return (MandelbulbDE((modelMat * vec4(p, 1.)).xyz, 8.));
	return (MandelbulbDE((modelMat * vec4(p * SCALE, 1.)).xyz, 8.) / SCALE);

	// return (MandelbulbDE(p, 8.));
}

float refShortestDistanceToSurface(vec3 eyeP, vec3 marchinDir, float start, float end)
{
	float depth = start;
	float dist;
	for (int i = 0; i < MAX_STEPS_REF; i++)
	{
		dist = DistanceEstimation(eyeP + marchinDir * depth);
		if (dist < EPSILON_REF)
			return (depth);
		depth += dist;
		if (depth > end ||
			(depth > end - EPSILON_REF && depth < end + EPSILON_REF))
			return end;
	}
	return (end);
}

float ShortestDistanceToSurface(vec3 eyeP, vec3 marchinDir, float start, float end)
{
	float depth = start;
	float dist;
	for (int i = 0; i < MAX_STEPS; i++)
	{
		dist = DistanceEstimation(eyeP + marchinDir * depth);
		if (dist < EPSILON)
			return (depth);
		depth += dist;
		if (depth > end ||
			(depth > end - EPSILON && depth < end + EPSILON))
			return end;
	}
	return (end);
}

vec3 estimateNormal(vec3 p)
{
	float n = DistanceEstimation(p);
	float dx = DistanceEstimation(p + vec3(EPSILON, 0, 0));
	float dy = DistanceEstimation(p + vec3(0, EPSILON, 0));
	float dz = DistanceEstimation(p + vec3(0, 0, EPSILON));
	return (normalize(vec3(dx - n, dy - n, dz - n)));
}

vec3 phongLight(s_light light, vec3 vEP, vec3 norm, vec3 pos, vec3 colorObj)
{
	vec3 vPL = normalize(light.pos - pos);
	vec3 vReflectLN = normalize(reflect(-vPL, norm));
   
	float diffuse = dot(vPL, norm);
	float specular = dot(vReflectLN, vEP);
		
	if (diffuse < EPSILON)
		return (vec3(0., 0., 0.));
	if (specular < EPSILON)
		return (light.intensity * (colorObj * diffuse * K_D));

	return (light.intensity * (colorObj * diffuse * K_D
		+ light.colorLight * pow(specular, K_S)));
}


//////// AMBIANT LIGHT ////////
#define HASHSCALE1 .1031
const float PI = 3.14159265359;

float hash(float p)
{
	vec3 p3 = fract(vec3(p) * HASHSCALE1);
	p3 += dot(p3, p3.yzx + 19.19);
	return fract((p3.x + p3.y) * p3.z);
}

vec3 randomSphereDir(in vec2 rnd)
{
	float s = rnd.x * PI * 2.;
	float t = rnd.y * 2. - 1.;
	return vec3(sin(s), cos(s), t) / sqrt(1.0 + t * t);
}
vec3 randomHemisphereDir(in vec3 dir, in float i)
{
	vec3 v = randomSphereDir( vec2(hash(i + 1.), hash(i + 2.)) );
	return (v * sign(dot(v, dir)));
}

float ambientOcclusion(in vec3 p, in vec3 n, in float maxDist, in float falloff)
{
	const int nbIte = MAX_AO_STEPS;
	const float nbIteInv = 1. / float(nbIte);
	const float rad = 1. - 1. * nbIteInv; //Hemispherical factor (self occlusion correction)
		
	float ao = 0.0;
		
	for (int i = 0; i < nbIte; i++)
	{
		float l = hash(float(i)) * maxDist;
		vec3 rd = normalize(n + randomHemisphereDir(n, l) * rad) * l; // mix direction with the normal
																		// for self occlusion problems!
		ao += (l - max(DistanceEstimation(p + rd), 0.)) / maxDist * falloff;
	}
	
	return clamp(1. - ao * nbIteInv, 0., 1.);
}

////////////////////////////////

#define LIGHT_RADIUS 15.

float shadows(in vec3 posHit, in vec3 vPL, float minDist, float maxDist, float k)
{
	float dist = 1.;
	float lightRes = 1.;
	vec3 posAlongLight;
	float rayProgress = minDist;

	for(int i = 0; i < 64; i++)
	{
		posAlongLight = posHit + vPL * rayProgress;
		if (rayProgress > maxDist)
		{
			float fadeRatio = 1. - clamp(maxDist / LIGHT_RADIUS, 0., 1.);
			float distanceFactor = pow(fadeRatio, 2.);
			return (lightRes * distanceFactor);
		}
		dist = DistanceEstimation(posAlongLight);
		lightRes = min(lightRes, k * dist / rayProgress);
		if (dist < EPSILON)
			return (0.0);
		rayProgress += dist;
	}
	return (0.);
}

vec3 calculateColor(s_light light, vec3 eye, vec3 pos, vec3 norm)
{
	vec3 colorObj = COLOR_OBJ;
	// vec3 ambiantLight = colorObj * K_A;
	vec3 ambiantLight = colorObj * ambientOcclusion(pos, norm, 2., 1.2) * K_A;
	vec3 vEP = normalize(eye - pos);
	vec3 color = vec3(0.);
		
	color += phongLight(light, vEP, norm, pos, colorObj);
		
	pos += norm * 0.01;
	float sh = shadows(pos, normalize(light.pos - pos),
		0., distance(light.pos, pos), 10.);
		
	color *= sh;
	color += ambiantLight;
	return (color);

}

vec3	calculateMarchinDir(float fov, vec2 resolutionSize, vec2 fragCoord)
{

	// vec2 xy = fragCoord - resolutionSize / 2.0 ;
	// float z = resolutionSize.y / tan(radians(fov));
	// return (normalize(vec3(xy, -z)));

	float	ratio = resolutionSize.x / resolutionSize.y;
	vec2	xy = (fragCoord - 0.5) / resolutionSize;
	//from [0,1] to [-1, 1]
	xy.x = (2 * xy.x - 1) * ratio * tan(radians(fov / 2.));
	xy.y = (2 * xy.y - 1) * tan(radians(fov / 2.));
	return (normalize(vec3(xy, -1)));
}

void	main(void)
{
	float	d = distance(eye, modelPos);

	vec3	dir = calculateMarchinDir(u_fov, u_resolution, gl_FragCoord.xy);
	vec3	worldDir = (inverseView * vec4(dir, 0.0)).xyz;

	float	dist = ShortestDistanceToSurface(eye, worldDir, d - 1.5, farNear[0]);

	vec3	posHit = eye + worldDir * dist;
	vec3	norm = estimateNormal(posHit);

	if (dist > farNear[0] - EPSILON)
	{
		gl_FragDepth = farNear[0];
		FragColor = vec4(0.);
		return ;
	}
	s_light light[2];
	light[0].pos = u_lightPos;
	light[0].colorLight = vec3(1.0, 1.0, 1.0);
	light[0].intensity = 0.5;

	vec3 color = calculateColor(light[0], eye, posHit, norm);

	// for (int i = 0; i < MAX_REFLECTIONS; i++) // Reflexion
	// {
	// 	worldDir = reflect(worldDir, norm);
	// 	posHit += norm * 0.03;
	// 	dist = refShortestDistanceToSurface(posHit, worldDir, MIN_DIST, MAX_DIST);

	// 	posHit = posHit + worldDir * dist;
	// 	norm = estimateNormal(posHit);

	// 	if (dist > MAX_DIST - EPSILON_REF)
	// 	{
	// 		fragColor = vec4(color + K_R * texture(iChannel0, worldDir).xyz, 1.);
	// 		return;
	// 	}
	// 	else 
	// 		color += K_R * calculateColor(light, eye, posHit, norm) * float((MAX_REFLECTIONS - i) / MAX_REFLECTIONS);
	// }

	float	p10 = projection[2].z;
	float	p11 = projection[3].z;
	float eyeHitZ  = -dist * dot(worldDir, (vec3(0.,0.,-1.) * mat3(view)));
	float ndcDepth = -p10 + -p11 / eyeHitZ;
	// from [-1,1] to [0,1]
	float dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	gl_FragDepth = dep;

	FragColor = vec4(color, 1.0);
}