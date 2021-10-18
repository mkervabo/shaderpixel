#version 410 core

out vec4			FragColor;

uniform mat4		view;
uniform vec3		eye;
uniform float		time;
uniform sampler2D	text;

uniform mat4		inverseView;
uniform mat4		projection;
uniform float		farNear[2];
uniform float		u_fov;
uniform vec2		u_resolution;
uniform vec3		u_lightPos;

const int MAX_REFLECTIONS = 1;
const int MAX_STEPS = 400;
const int MAX_STEPS_REF = 100;
const int MAX_STEPS_DENSITY = 64; // 32
const int MAX_STEPS_SHADOWS = 16; // 32
const int MAX_AO_STEPS = 32;
const float MIN_DIST = 0.1;
const float MAX_DIST = 100.0;
const float EPSILON = 0.0025;
const float EPSILON_REF = 0.0025;
const int T_SIZEX = 12;
const int T_SIZEY = 12;

const float BOUND = .5;

#define K_A 0.4
#define K_S 50.
#define K_D 1.
#define K_R 0.2
#define INCIDENCE 1.02
#define K_T 0.5
#define K_LIGHT 5.
#define DENS_F 2. // 1.
#define SHAD_DENS_F 5.5 // 3.5
#define THRESHOLD 0.8 // 0.8

vec3 rotY(vec3 p, float theta)
{
	return (p * mat3(
		vec3(cos(theta), 0., sin(theta)),
		vec3(0., 1., 0.),
		vec3(-sin(theta), 0., cos(theta))));
}

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
};

struct s_ray
{
	vec3 eyeP;
	vec3 dir;
	vec3 localCam;
	float w;
	mat4 viewToWorld;
};

struct s_env
{
	s_ray ray;
	s_light light;
	bool isDifSpecSha[3];
	int typeHit;
};

s_obj unionSDF(s_obj obj1, s_obj obj2)
{
	if (obj1.dist < obj2.dist)
		return (obj1);
	return (obj2);
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

float planDE( vec3 p, vec3 n, float h )
{
	// n must be normalized
	return dot(p,n) + h;
}

#define NONE -1
#define CLOUD 0
#define CUBE 1
#define SPHERE 2
#define SPHERE_2 3

s_obj DistanceEstimation(vec3 p, int typeTouch)
{
	s_obj cube;
	cube.type = CUBE;
	cube.color = vec4(0.1, 0.5, 0.7, 1.);
	cube.dist = boxDE(p + vec3(-2., 0.5, 0.), vec3(1.));

	s_obj sphere;
	sphere.type = SPHERE;
	sphere.color = vec4(0.1, 0.5, 0.7, 1.);
	sphere.dist = sphereDE(vec3(-1., -0.25, 0.) + rotY(p, time * 0.5), 0.1);
	s_obj scene = unionSDF(cube, sphere);

	s_obj sphere2;
	sphere2.type = SPHERE_2;
	sphere2.color = vec4(0.5, 0.1, 0.7, 1.);
	sphere2.dist = sphereDE(p + vec3(0., 0., -0.3 + cos(time * 0.5)), 0.1);
	scene = unionSDF(scene, sphere2);

	if (typeTouch == CLOUD)
		return (scene); 

	s_obj cloud;
	cloud.type = CLOUD;
	cloud.color = vec4(1.);
	cloud.dist = boxDE(p, vec3(BOUND));

	scene = unionSDF(cloud, scene);
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

///// DENSITY /////
vec2 convert1dTo2d(float xsize, float index)
{
	vec2 xyIdx;
		
	xyIdx.x = mod(index, xsize);
	xyIdx.y = xsize - floor(index / xsize);
	return (xyIdx);
}

vec4 pseudoVolumeTexture(vec3 pos)
{
	//float att = 30. + 10. * sin(time);
	pos = pos + 0.5;// + 0.5; // / 2. permet le grossissement et 0.5 permet de le centré (le centre du cube est en 0.)
	//pos = floor(pos * att) / att;
	pos.z += 0.06;
	pos.x = clamp(pos.x, 0., 1.);
	pos.y = clamp(pos.y, 0., 1.);
	pos.z = clamp(pos.z, 0.075, 1.09);
		
	float xsize = float(T_SIZEX); // 12
	float numframes = xsize * float(T_SIZEY); // 12
		
	float zphase = fract(pos.z * numframes);
	float zframe = pos.z * numframes - zphase;

	vec2 uv = fract(pos.xy);
	uv /= xsize;

	vec2 curframe = convert1dTo2d(xsize, zframe) / xsize;
	vec2 nextframe = convert1dTo2d(xsize, zframe + 1.) / xsize;

	vec4 sampleA = textureLod(text, uv + curframe, 0.);
	vec4 sampleB = textureLod(text, uv + nextframe, 0.);

	return mix(sampleA, sampleB, zphase);
}

struct s_density
{
	vec3 lightEnergy;
	float transmittance;
	float distT;
};

struct s_cloud
{
	float curDensity;
	float curVolTxt;
		
	vec3  lightEnergy;
	float transmittance;
		
	float stepSize;
	float shadowStepSize;
		
	vec3 lPos;
	vec3 curPos;
		
	vec3 inPos;
	vec3 outPos;
};

void shadowCloud(inout s_cloud cloud, vec3 lightDir, float sh)
{
	float DensityFactor = DENS_F * cloud.stepSize;
	float ShadowDensityFactor = SHAD_DENS_F * cloud.shadowStepSize;
	float shadowtransmittance = 0.;
	vec3	absorbedLight = vec3(0.);
	
	float MaxShadowDist = float(MAX_STEPS_SHADOWS) / 1.5;
	float shadowDist;
	float curShadowVolTxt;
	
	shadowDist = 0.;
	cloud.lPos = cloud.curPos;
	if (sh < 0.1) // S'il y a de l'ombre sur le nuage
		shadowDist = MaxShadowDist;
	else
	{
		for (int iS = 0; iS < MAX_STEPS_SHADOWS; iS++)
		{
			cloud.lPos += lightDir;
			curShadowVolTxt = pseudoVolumeTexture(cloud.lPos).r;
			shadowDist += curShadowVolTxt;

			if (cloud.lPos.x > BOUND || cloud.lPos.x < -BOUND
				|| cloud.lPos.y > BOUND || cloud.lPos.y < -BOUND
					|| cloud.lPos.z > BOUND || cloud.lPos.z < -BOUND) break;
		}
	}
	cloud.curDensity = min(cloud.curVolTxt * DensityFactor, 1.);
	shadowtransmittance = exp(-shadowDist * ShadowDensityFactor); // t = e^(-t * d)
	absorbedLight = vec3(shadowtransmittance * cloud.curDensity);
	
	cloud.lightEnergy += absorbedLight * cloud.transmittance;
	cloud.transmittance *= 1. - cloud.curDensity;
}

s_density ambiantCloud(inout s_cloud cloud)
{
	float shadowDist = 0.;

	cloud.lPos = cloud.curPos + vec3(0,0,0.05);
	float lsample = pseudoVolumeTexture(cloud.lPos).r;
	shadowDist += lsample;
	cloud.lPos = cloud.curPos + vec3(0,0,0.1);
	lsample = pseudoVolumeTexture(cloud.lPos).r;
	shadowDist += lsample;
	cloud.lPos = cloud.curPos + vec3(0,0,0.2);
	lsample = pseudoVolumeTexture(cloud.lPos).r;
	shadowDist += lsample;

	float AmbientDensity = 0.3;
	vec3 SkyColor = vec3(0.57, 0.75, 0.94);
		
	cloud.lightEnergy += exp(-shadowDist * AmbientDensity) * cloud.curDensity * SkyColor * cloud.transmittance;
	return (s_density(cloud.lightEnergy * K_LIGHT, cloud.transmittance, distance(cloud.outPos, cloud.inPos)));
}

s_density getDensity(s_env env, vec3 curP, vec3 dir, vec3 lightDir, float sh)
{
	s_cloud cloud = s_cloud(0.,0., vec3(0.),1.,
		1. / float(MAX_STEPS_DENSITY), 1. / float(MAX_STEPS_SHADOWS), vec3(0.), curP, curP, vec3(0.));
		
	lightDir *= cloud.shadowStepSize;
	dir *= cloud.stepSize;
	for (int i = 0; i < MAX_STEPS_DENSITY; i++)
	{
		cloud.curVolTxt = pseudoVolumeTexture(cloud.curPos).r;
		if (cloud.curVolTxt > 0.01) // light calcul
			shadowCloud(cloud, lightDir, sh); //
		cloud.curPos += dir;
		if (cloud.transmittance < THRESHOLD) break;
	}
	cloud.outPos = cloud.curPos;
	return (ambiantCloud(cloud));
}

float getOnlyDensity(vec3 curP, vec3 dir)
{
	float stepSize = 1. / float(MAX_STEPS_DENSITY);
	float Density = DENS_F;
	float curDens = 0.;
	float curVolTxt;

	dir *= stepSize;
	for (int i = 0; i < MAX_STEPS_DENSITY; i++)
	{
		curVolTxt = pseudoVolumeTexture(curP).r;
		curDens += curVolTxt;
		curP += dir;
	}
	return min(curDens * stepSize * DENS_F, 1.);
}

///// DENSITY /////

float softShadow(s_env env, float mint, float maxt, float k, int type)
{
	float h;
	s_obj obj;
	float res = 1.0;
	vec3 p;

	for( float t=mint; t<maxt; )
	{
		p = env.ray.eyeP + env.ray.dir * t;
		obj = DistanceEstimation(p, type);
		h = obj.dist;
		if (h < EPSILON)
		{
			if (obj.type == CLOUD)
			{
				res = (1. - getOnlyDensity(p, env.ray.dir));
				type = CLOUD;
			}
			else
				return 0.;
		}
		if (obj.type != CLOUD)
			res = min(res, k * h / t);
		t += h;
	}
	return res;
}

vec3 phongLight(s_light light, vec3 vEP, vec3 norm, vec3 pos, bool isDifSpecSha[3], vec3 colorObj)
{
	vec3 vPL = normalize(light.pos - pos);
	vec3 vReflectLN = normalize(reflect(-vPL, norm));
	 
	float diffuse = dot(vPL, norm);
	float specular = dot(vReflectLN, vEP);
		
	if (diffuse < EPSILON)
		return (vec3(0., 0., 0.));
	if (specular < EPSILON)
		return (light.intensity * (colorObj * diffuse * K_D));

	vec3 ret = vec3(0.);
		
	ret = light.intensity * (colorObj * diffuse * K_D);
	ret += light.intensity * (light.colorLight * pow(specular, K_S));
	return (ret);
}

float calcShadow(s_env env, vec3 pos, int type)
{
	env.ray.eyeP = pos;
	env.ray.dir = normalize(env.light.pos - pos);
	float sh = softShadow(env, 0.,
		distance(env.light.pos, pos), 30., type);
	return (sh);
}

vec3 calculateColor(s_env env, vec3 pos, vec3 norm, vec3 colorObj)
{
	vec3 ambiantLight = colorObj * K_A;
	vec3 vEP = normalize(env.ray.eyeP - pos);
	vec3 colorShadow = vec3(0.);
	vec3 color;
		
	color = phongLight(env.light, vEP, norm, pos, env.isDifSpecSha, colorObj);
		
	pos += norm * 0.01;
	if (env.isDifSpecSha[2])
	{
		float sh = calcShadow(env, pos, NONE);
		color *= clamp(sh, 0., 1.);
	}
	color += ambiantLight;
	return (color);
}

s_hit ShortestDistanceToSurface(s_env env, float start, float end, inout vec4 dColorObj)
{
	vec3	color;
	float	depth = start;
	vec3	newPos;
	vec3	norm;
	s_hit	hit;
	s_obj	obj;
	float	coef = 1.;
	float	distT = 0.;
	vec3	inPosCloud;
	bool	isCloudPrinted = false;

	hit.typeHit = -1;
	for (int i = 0; i < MAX_STEPS; i++)
	{
		newPos = env.ray.eyeP + env.ray.dir * depth;
		obj = DistanceEstimation(newPos, hit.typeHit);
		if (obj.dist < EPSILON) // Si on touche un obj
		{
			color = obj.color.rgb;
			hit.posHit = newPos;
			hit.dist = depth;
			hit.typeHit = obj.type;
			if (obj.type == CLOUD) // Si on touche le nuage
			{
				isCloudPrinted = true;
				inPosCloud = hit.posHit;
				norm = estimateNormal(hit.posHit, NONE);
				float sh = calcShadow(env, hit.posHit + norm * 0.01, hit.typeHit);
			
				s_density density = getDensity(env, hit.posHit, env.ray.dir,
					normalize(env.light.pos - hit.posHit), sh);
				dColorObj.rgb = env.light.colorLight * (1. - density.transmittance)
					+ density.lightEnergy * density.transmittance;
				coef = density.transmittance;
				distT = density.distT;
			}
			else
			{
				norm = estimateNormal(hit.posHit, NONE);
				if (distT > 0.01) // Si un objet et devant ou derriere le nuage (permet d'augmenter l'opacité en fonction de la profondeur)
				{ 
					float d = 0.;
					if (coef < 0.9)
						d = min(distance(hit.posHit, inPosCloud), distT) / distT;
					dColorObj.rgb += calculateColor(env, hit.posHit, norm, color).rgb * coef * (1. - d);
				}
				else
					dColorObj.rgb += calculateColor(env, hit.posHit, norm, color).rgb * coef;
				return (hit);
			}
		}
		depth += obj.dist;
		if (depth > end - EPSILON) // Si aucun obj n'est detecter
		{
			dColorObj.rgb += vec3(0.);
			dColorObj.a = isCloudPrinted ? (coef < 0.9 ? 1. : 1. - coef) : 0.;
			hit.dist = isCloudPrinted ? distance(inPosCloud, eye) : end;
			return (hit);
		}
	}
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
	env.ray.localCam = calculateMarchinDir(u_fov, u_resolution, gl_FragCoord.xy);
	env.ray.eyeP = eye;
	env.isDifSpecSha = bool[3](true, true, true);

	env.ray.viewToWorld = view;

	env.ray.dir = (inverseView * vec4(env.ray.localCam, 0.0)).xyz; // worldDir

	vec4 dColorObj = vec4(vec3(0.), 1.);

	env.light.pos = u_lightPos;
	// env.light.pos = vec3(-4., 2., -1.);
	env.light.colorLight = vec3(0.25, 0., 0.45);
	env.light.intensity = 0.5;
	s_hit hit = ShortestDistanceToSurface(env, MIN_DIST, MAX_DIST, dColorObj);

	float	p10 = projection[2].z;
	float	p11 = projection[3].z;
	float eyeHitZ  = -hit.dist * dot(env.ray.dir, (vec3(0.,0.,-1.) * mat3(view)));
	float ndcDepth = -p10 + -p11 / eyeHitZ;
	// from [-1,1] to [0,1]
	float dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	gl_FragDepth = dep;

	FragColor = dColorObj;
}