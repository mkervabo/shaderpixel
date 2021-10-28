#version 410 core

out vec4		FragColor;
in	vec2		textureCoord;
in	vec3		norm;

uniform mat4	view;
uniform vec3	eye;
uniform float	time;

uniform int		u_isSpecular;
uniform int		u_isDiffuse;

uniform mat4	inverseView;
uniform mat4	projection;
uniform float	farNear[2];
uniform float	u_fov;
uniform vec2	u_resolution;
uniform vec3	u_lightPos;
uniform vec3	modelPos;

const int MAX_REFLECTIONS = 1;
const int MAX_STEPS = 300;
const int MAX_STEPS_REF = 300;
const int MAX_AO_STEPS = 30;
const float MIN_DIST = 0.1;
const float MAX_DIST = 100.0;
const float EPSILON = 0.0025;
const float EPSILON_REF = 0.001;

#define K_A 0.2
#define K_SHIN 30.
#define K_D 0.9
#define K_S 1.
#define K_R 0.1
#define INCIDENCE 1.02
#define K_T 1.5

struct s_light
{
	vec3 pos;
	vec3 colorLight;
	float intensity;
};

struct s_obj
{
	int type;
	vec4 color;
	float dist;
};

struct s_hit
{
	vec3 posHit;
	int typeHit;
	float dist;
	vec3 ambiantColor;
};

struct s_ray
{
	vec3 eyeP;
	vec3 start;
	vec3 dir;
};

struct s_env
{
	s_ray ray;
	s_light light;
	bool isDifSpecSha[3];
	int typeHit;
	vec3 posHitT;
};

struct s_color
{
	vec3 color;
	vec3 ambiant;
};

s_obj unionSDF(s_obj obj1, s_obj obj2)
{
	if (obj1.dist < obj2.dist)
		return (obj1);
	return (obj2);
}

float smoothUnion( float d1, float d2, float k )
{
	float h = clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
	return (mix( d2, d1, h ) - k * h * (1.0 - h));
}

float sphereDE(vec3 p, float rayon)
{
	return (length(p) - rayon);
}

float boxDE(vec3 p, vec3 b)
{
	vec3 q = abs(p) - b;
	return (length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0));
}

float sdPlane( vec3 p, vec3 n, float h )
{
	// n must be normalized
	return dot(p,n) + h;
}

#define NONE -1
#define SPHERE 0
#define CUBE 1
#define CUBE_2 2
#define CUBE_3 3
#define CUBE_4 4
#define CUBE_5 5

s_obj DistanceEstimation(vec3 p, int typeTouch)
{
	p -= modelPos;
	s_obj sphere;
	sphere.type = SPHERE;
	sphere.color = vec4(0.6, 0., 0.7, 0.6);
	sphere.dist = sphereDE(p, 0.5);
		
	s_obj plan; // bottom
	plan.type = CUBE;
	plan.color = vec4(0.3, 0.7, 0.6, 1.);
	plan.dist = sdPlane(p + vec3(0.3, 2., 0.), vec3(0., 1., 0.), 0.);

	s_obj plan2; // front
	plan2.type = CUBE_2;
	plan2.color = vec4(0.3, 0.7, 0.6, 1.);
	plan2.dist = sdPlane(p + vec3(0.3, 0., 1.), vec3(0., 0., 1.), 0.);

	s_obj plan3; // left
	plan3.type = CUBE_3;
	plan3.color = vec4(0.3, 0.7, 0.6, 1.);
	plan3.dist = sdPlane(p + vec3(2.05, 0., 0.), vec3(1., 0., 0.), 0.);

	s_obj plan4; // right
	plan4.type = CUBE_4;
	plan4.color = vec4(0.3, 0.7, 0.6, 1.);
	plan4.dist = sdPlane(p + vec3(-1.7, 0., 0.), vec3(-1., 0., 0.), 0.);

	s_obj plan5;// top
	plan5.type = CUBE_5;
	plan5.color = vec4(0.3, 0.7, 0.6, 1.);
	plan5.dist = sdPlane(p + vec3(0.3, -1.98, 0.), vec3(0., -1., 0.), 0.);


	s_obj scene = unionSDF(plan, plan2);
	scene = unionSDF(scene, plan3);
	scene = unionSDF(scene, plan4);
	scene = unionSDF(scene, plan5);
	if (typeTouch != sphere.type)
		scene = unionSDF(scene, sphere);
	return (scene);
}

vec3 estimateNormal(vec3 p, int typeHit)
{
	return (normalize(vec3(DistanceEstimation(vec3(p.x + EPSILON, p.y, p.z), typeHit).dist
		- DistanceEstimation(vec3(p.x - EPSILON, p.y, p.z), typeHit).dist,
			DistanceEstimation(vec3(p.x, p.y + EPSILON, p.z), typeHit).dist
		- DistanceEstimation(vec3(p.x, p.y - EPSILON, p.z), typeHit).dist,
			DistanceEstimation(vec3(p.x, p.y, p.z + EPSILON), typeHit).dist
		- DistanceEstimation(vec3(p.x, p.y, p.z - EPSILON), typeHit).dist)));
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
		ao += (l - max(DistanceEstimation(p + rd, NONE).dist, 0.)) / maxDist * falloff;
	}
	
	return clamp(1. - ao * nbIteInv, 0., 1.);
}

////////////////////////////////

vec3 phongLight(s_light light, vec3 vPToEye, vec3 norm, vec3 pos, bool isDifSpecSha[3], vec3 colorObj)
{
	vec3 vPL = normalize(light.pos - pos);
	vec3 rL = reflect(vPL, norm);
		
	float diffuse = dot(vPL, norm);
	float specular = dot(-rL, vPToEye);
		
	if (diffuse < EPSILON)
		return (vec3(0., 0., 0.));
	if (specular < EPSILON)
	{
		if (isDifSpecSha[0])
			return (light.intensity * (colorObj * diffuse * K_D));
		return (vec3(0.));
	}
	vec3 ret = vec3(0.);
		
	if (isDifSpecSha[0]) // diffuse
		ret += light.intensity * (colorObj * diffuse * K_D);
	if (isDifSpecSha[1]) // specular
		ret += light.intensity * (light.colorLight * pow(specular, K_SHIN) * K_S);
	return (ret);
}

float softShadow(s_env env, float mint, float maxt, float k)
{
	float h;
	s_obj obj;
	float res = 1.0;
	vec3 pos;

	for( float t=mint; t<maxt; )
	{
		pos = env.ray.start + env.ray.dir * t;
		obj = DistanceEstimation(pos, NONE);
		h = obj.dist;
		if (h < EPSILON)
			return 0.;
		res = min(res, k * h / t);
		t += h;
	}
	return res;
}

s_color calculateColor(s_env env, vec3 pos, vec3 norm, vec3 colorObj, bool isAmbiant)
{
	vec3 ambiantLight = vec3(0.);
	vec3 vPToEye = normalize(env.ray.eyeP - pos);
	vec3 color = vec3(0.);
		
	if (isAmbiant)
		ambiantLight = colorObj * K_A;
		// ambiantLight = colorObj * ambientOcclusion(pos, norm, 2., 1.3) * K_A;

	color = phongLight(env.light, vPToEye, norm, pos, env.isDifSpecSha, colorObj);
	pos += norm * 0.01;
	if (env.isDifSpecSha[2] && env.isDifSpecSha[0])
	{
		env.ray.start = pos;
		env.ray.dir = normalize(env.light.pos - pos);
		float sh = softShadow(env, 0.,
		 distance(env.light.pos, pos), 150.);
		sh = max(sh, 0.3);
		color *= sh;
	}
	return (s_color(color, ambiantLight));
}

s_hit refShortestDistToSurf(s_env env, float start, inout vec3 norm, float end, inout vec3 dColorObj)
{
	vec3 color = vec3(0.);
	float depth = start;
	vec3 newPos;
	s_hit hit;
	hit.ambiantColor = vec3(0.);
	hit.typeHit = NONE;
	s_obj obj;
	for (int i = 0; i < MAX_STEPS_REF; i++)
	{
		newPos = env.ray.start + env.ray.dir * depth;
		obj = DistanceEstimation(newPos, hit.typeHit);
		if (obj.dist < EPSILON_REF) // Si on touche un obj
		{
			color = obj.color.rgb;
			hit.posHit = newPos;
			hit.dist = depth;
			norm = estimateNormal(hit.posHit, NONE);
			dColorObj += calculateColor(env, hit.posHit, norm, color, false).color;
			return (hit);
		}
		depth += obj.dist;
		if (depth > end - EPSILON_REF) // Si aucun obj n'est detecter
		{
			// dColorObj += texture(iChannel0, env.ray.dir).rgb;
			hit.dist = end;
			return (hit);
		}
	}
	hit.dist = end;
	// dColorObj += texture(iChannel0, env.ray.dir).rgb;
	return (hit);
}

void calculateColorBehind(s_env env, vec3 posHit, float end, inout vec3 dColorObj)
{
	vec3 color = vec3(0.);
	vec3 norm;
	s_hit secondHit;

	env.ray.start = posHit;
	env.ray.dir = -env.ray.dir;
	env.isDifSpecSha[2] = false;
	secondHit = refShortestDistToSurf(env, 0.1, norm, end, color);
	dColorObj += calculateColor(env, secondHit.posHit, norm, color, false).color;
}

s_color calculateTranslucentLight(s_env env, vec3 posHit, float end)
{
	s_color sColor = s_color(vec3(0.), vec3(0.));
	vec3 pos = env.light.pos;
	vec3 norm;
	vec3 dir = normalize(posHit - env.light.pos);
	float depth = 0.;
	s_obj obj;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		pos = pos + dir * depth;
		obj = DistanceEstimation(pos, NONE);
		if (obj.dist < EPSILON) // Si on touche un obj
		{
			if (obj.type == SPHERE)
			{
				norm = estimateNormal(pos, NONE);
				sColor = calculateColor(env, pos, norm, obj.color.rgb, true);
				return (sColor);
			}
			return (s_color(vec3(0.), vec3(0.)));
		}
		else if (depth > end - EPSILON) // Si aucun obj n'est detecter
			return (s_color(vec3(0.), vec3(0.)));

		depth = obj.dist;
	}
	return (s_color(vec3(0.), vec3(0.)));
}

vec3 reflexion(s_env env, vec3 norm, float end, inout vec3 ambiantColor)
{
	s_color sColor;
	vec3 color = vec3(0.);
	vec3 finalColor = vec3(0.);
	s_hit hit;
	hit.ambiantColor = vec3(0.);
	hit.typeHit = NONE;

	for (int i = 0; i < MAX_REFLECTIONS; i++) // Reflexion
	{
		env.ray.dir = reflect(env.ray.dir, norm);
		hit = refShortestDistToSurf(env, 0.1, norm, end, color);

		if (hit.dist > end - EPSILON_REF)  // Si on ne touche pas d'obj
		{
			//finalColor += texture(iChannel0, env.ray.dir).xyz * K_R * (1. / float(MAX_REFLECTIONS));
			return (finalColor);
		}
		sColor = calculateColor(env, hit.posHit, norm, color, true);
		color = sColor.color * K_R * (1. / float(MAX_REFLECTIONS));
		ambiantColor += sColor.ambiant;
		
		env.ray.eyeP = env.light.pos; // Eclairage au sol a travers l'objet transparent
		sColor = calculateTranslucentLight(env, hit.posHit, end - EPSILON_REF);
		color += sColor.color * K_T;
		
		env.ray.start = env.ray.start + env.ray.dir * hit.dist;
		finalColor += color;
	}
	return (finalColor);
}

s_hit ShortestDistanceToSurface(s_env env, float start, float end, inout vec3 dColorObj)
{
	vec3 color = vec3(0.);
	float depth = distance(eye, modelPos) - 1.5;
	vec3 newPos;
	vec3 norm;
	s_hit hit;
	hit.ambiantColor = vec3(0.);
	s_obj obj;
	bool isOneTrans = false;
	hit.typeHit = NONE;
	for (int i = 0; i < MAX_STEPS; i++)
	{
		newPos = env.ray.start + env.ray.dir * depth;
		obj = DistanceEstimation(newPos, hit.typeHit);
		if (obj.dist < EPSILON) // Si on touche un obj
		{
			color = obj.color.rgb;
			hit.posHit = newPos;
			hit.dist = depth;
			hit.typeHit = obj.type;
			norm = estimateNormal(hit.posHit, NONE);
			if (!(obj.color.a > 1. - EPSILON)) // Si l'objet est transparant
			{
				s_color sColor;
				isOneTrans = true;
				env.posHitT = hit.posHit;
				sColor = calculateColor(env, hit.posHit, norm, color, true);
				dColorObj += sColor.color;
				hit.ambiantColor += sColor.ambiant;
				hit.posHit += norm * 0.01;
				env.ray.start = hit.posHit;
				dColorObj += reflexion(env, norm, end - depth, hit.ambiantColor);
				env.ray.dir = refract(env.ray.dir, norm, INCIDENCE);
			}
			else // Si l'objet est opaque
			{
				s_color sColor;
				env.typeHit = hit.typeHit;
				sColor = calculateColor(env, hit.posHit, norm, color, true);
				dColorObj += sColor.color;
				hit.ambiantColor += sColor.ambiant;
				// if (isOneTrans)
				// 	calculateColorBehind(env, hit.posHit, end, dColorObj);
				
				env.ray.eyeP = env.light.pos; // Eclairage au sol a travers l'objet transparent
				sColor = calculateTranslucentLight(env, hit.posHit, end - depth);
				dColorObj += sColor.color * K_T;
				return (hit);
			}
		}
		depth += obj.dist;
		if (depth > end - EPSILON) // Si aucun obj n'est detecter
		{
			// dColorObj += texture(iChannel0, env.ray.dir).rgb;
			if (isOneTrans)
				calculateColorBehind(env, newPos, end, dColorObj);
			else
				hit.dist = end;
			return (hit);
		}
	}
	// dColorObj += texture(iChannel0, env.ray.dir).rgb;
	if (isOneTrans)
		calculateColorBehind(env, newPos, end, dColorObj);
	else
		hit.dist = end;
	return (hit);
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

void main(void)
{
	s_env env;
	env.ray.dir = calculateMarchinDir(u_fov, u_resolution, gl_FragCoord.xy);
	env.ray.eyeP = eye;
	env.isDifSpecSha = bool[3](bool(u_isDiffuse), bool(u_isSpecular), true);
	env.ray.start = env.ray.eyeP;

	env.ray.dir = (inverseView * vec4(env.ray.dir, 0.0)).xyz; // worldDir
	vec3 dColorObj= vec3(0.);

	// env.light.pos = u_lightPos;
	env.light.pos = vec3(cos(time), sin(time), 0.8) + modelPos;
	env.light.colorLight = vec3(1.0, 1.0, 1.0);
	env.light.intensity = 0.5;

	s_hit hit = ShortestDistanceToSurface(env, farNear[1], MAX_DIST, dColorObj);
	dColorObj.rgb += hit.ambiantColor;

	if (hit.dist > MAX_DIST - EPSILON)
	{
		gl_FragDepth = farNear[0];
		FragColor = vec4(dColorObj.rgb, 1.);
		return ;
	}

	float	p10 = projection[2].z;
	float	p11 = projection[3].z;
	float eyeHitZ  = -hit.dist * dot(env.ray.dir, (vec3(0.,0.,-1.) * mat3(view)));
	float ndcDepth = -p10 + -p11 / eyeHitZ;
	// from [-1,1] to [0,1]
	float dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	gl_FragDepth = dep;

	FragColor = vec4(dColorObj, 1.0);
}