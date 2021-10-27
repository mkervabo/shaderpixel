#version 410 core

out vec4		FragColor;
in	vec2		textureCoord;
in	vec3		norm;

uniform mat4	modelMat;
uniform vec3	modelPos;
uniform mat4	view;
uniform vec3	eye;
uniform float	time;

uniform mat4	inverseView;
uniform mat4	projection;
uniform float	farNear[2];
uniform float	u_fov;
uniform vec2	u_resolution;
uniform vec3	u_lightPos;

const int MAX_ITERATIONS = 10;
const int MAX_STEPS = 100;
const int MAX_AO_STEPS = 10;
const float MIN_DIST = 0.001;
const float MAX_DIST = 100.;
const float EPSILON = 0.001;

const vec3 COLOR_SPHERE = vec3(0.6, 0.35, 0.2);

#define K_A 0.2
#define K_SHIN 3.
#define K_S 0.3
#define K_D 0.8
#define IT_SHADOWS 100
#define I_TERRAIN 8

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

float random (in vec2 st) {
	return fract(sin(dot(st.xy,
						 vec2(12.9898,78.233)))*
		43758.5453123);
}

vec4 unionSDF(vec4 a, vec4 b)
{
	return (a.w < b.w ? a : b);
}

float sphereDE(vec3 p, float rayon)
{
	return (length(p) - rayon);
}

float hash(vec3 p)  
{
	p  = 17.0*fract( p*0.3183099+vec3(.11,.17,.13) );
	return fract( p.x*p.y*p.z*(p.x+p.y+p.z) );
}

float sph( vec3 i, vec3 f, vec3 c )
{
	// random radius at grid vertex i+c
	float rad = hash(i + c) * 0.55;
	// distance to sphere at grid vertex i+c
	return length(f - c) - rad; 
}

float sdBase(vec3 p)
{
	vec3 i = floor(p);
	vec3 f = fract(p);
	// distance to the 8 corners spheres
	return min(min(min(sph(i,f,vec3(0,0,0)),
				  sph(i,f,vec3(0,0,1))),
				  min(sph(i,f,vec3(0,1,0)),
					  sph(i,f,vec3(0,1,1)))),
			  min(min(sph(i,f,vec3(1,0,0)),
					  sph(i,f,vec3(1,0,1))),
				  min(sph(i,f,vec3(1,1,0)),
					  sph(i,f,vec3(1,1,1)))));
}

vec2 sdFbm( vec3 p, float d)
{
	float s = 1.0;
	float t = 0.;
	for (int i = 0; i < I_TERRAIN; i++)
	{
		// evaluate new octave
		float n = s*sdBase(p);
		d = smax(d, -n, 0.2 * s);
		t += d;
		// prepare next octave
		p = mat3( 0.00, 1.60, 1.20,
				-1.60, 0.72,-0.96,
				-1.20,-0.96, 1.28 )*p;
		s = 0.5 * s;
	}
	return (vec2(d, t));
}

vec2 DistanceEstimation(vec3 p)
{
	p -= modelPos;
	p = (modelMat * vec4(p, 1.)).xyz;
	float sphere = sphereDE(p, 0.5);
		
	vec2 dt = sdFbm(p, sphere);
	dt.y = 1.0 + dt.y * 2.5;
	dt.y = dt.y * dt.y;

	return (dt);
}

vec2 iBox( in vec3 ro, in vec3 rd, in vec3 rad )
{
	ro -= modelPos;
	vec3 m = 1.0/rd;
	vec3 n = m*ro;
	vec3 k = abs(m)*rad;
	vec3 t1 = -n - k;
	vec3 t2 = -n + k;
	float tN = max( max( t1.x, t1.y ), t1.z );
	float tF = min( min( t2.x, t2.y ), t2.z );
	if( tN > tF || tF < 0.0)
		return vec2(-1.0);
	return vec2(tN, tF);
}

vec2 ShortestDistanceToSurface(vec3 eyeP, vec3 marchinDir, float start,
	float end)
{
	vec2 ret = vec2(0.);
	//bounding volume
	vec2 dis = iBox(eyeP, marchinDir, vec3(1.0));
	if( dis.y < 0.0 )
		return vec2(end, 0.);

	float depth = dis.x;
	vec2 h;
	for (int i = 0; i < MAX_STEPS; i++)
	{
		h = DistanceEstimation(eyeP + marchinDir * depth);
		ret.x = depth;
		ret.y = h.y;
		if (h.x < EPSILON ||  depth > dis.y)
			break;
		depth += h.x;
	}
	if (depth > dis.y) 
		ret = vec2(end, 0.);
	return (ret);
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

vec3 estimateNormal(vec3 p)
{
	return (normalize(vec3(DistanceEstimation(vec3(p.x + EPSILON, p.y, p.z)).x
		- DistanceEstimation(vec3(p.x - EPSILON, p.y, p.z)).x,
			DistanceEstimation(vec3(p.x, p.y + EPSILON, p.z)).x
		- DistanceEstimation(vec3(p.x, p.y - EPSILON, p.z)).x,
			DistanceEstimation(vec3(p.x, p.y, p.z + EPSILON)).x
		- DistanceEstimation(vec3(p.x, p.y, p.z - EPSILON)).x)));
}

float calcSoftShadow(vec3 ro, vec3 rd, float tmin, float tmax, float w)
{
	vec2 dis = iBox(ro, rd, vec3(1.0));
	if (dis.y < 0.0 )
		return (1.0);
		
	tmin = max(tmin,dis.x);
	tmax = min(tmax,dis.y);
		
	float t = tmin;
	float res = 1.0;
	for (int i = 0; i < IT_SHADOWS; i++)
	{
		float h = DistanceEstimation(ro + rd * t).x;
		res = min( res, h / (w * t) );
		t += clamp(h, 0.005, 1.);
		if (res < -1.0 || t > tmax)
			break;
	}
	return (res);
}

vec3 phongLight(s_light light, vec3 eye, vec3 dir, vec3 norm, vec3 pos, float mat)
{
	vec3 colorObj = mix(COLOR_SPHERE, vec3(1.), mat ) * 0.7;;
		
	vec3 vPToEye = normalize(eye - pos);
	vec3 vPL = normalize(light.pos - pos);
	float diffuse = dot(vPL, norm) * K_D;
		
	vec3 reflL = reflect(vPL, norm);
	float specular = dot(-reflL, vPToEye);

	if (diffuse < EPSILON)
		return (vec3(0., 0., 0.));

	diffuse *= calcSoftShadow(pos + norm * 0.01, normalize(light.pos - pos), MIN_DIST, MAX_DIST, 0.003);
	diffuse = clamp(diffuse, 0., 1.);
	vec3 ret;
	
	ret = light.intensity * (colorObj * 1.5 *vec3(1.,0.85,0.75) * diffuse);

	if (specular < EPSILON || diffuse < 0.1)
		return (ret);
	ret += light.intensity * (light.colorLight * pow(specular, K_SHIN) * K_S);
	return (ret);
}

vec3 calculateColor(s_light light, vec3 eye, vec3 dir, vec3 pos, vec3 norm, float mat)
{
	vec3 color;
		
	color = phongLight(light, eye, dir, norm, pos, mat);
	color += K_A * vec3(0.40,0.45,0.60) * mat * mat * mat * (0.1 * norm.y);

	//Reinhard tonemaping
	float exposure = 1.5;
	color *= exposure / (1. + color / exposure);

	//gamma
	color = pow(color, vec3(0.4545));
	return (color);
}

void main(void)
{
	float d = distance(eye, modelPos);
	vec3 dir = calculateMarchinDir(u_fov, u_resolution, gl_FragCoord.xy);

	vec3 worldDir = (inverseView * vec4(dir, 0.0)).xyz;
		
	vec2 dt = ShortestDistanceToSurface(eye, worldDir, d - 1.5, MAX_DIST);

	vec3 posHit = eye + worldDir * dt.x;
	vec3 norm = estimateNormal(posHit);

	if (dt.x > MAX_DIST - EPSILON)
	{
		gl_FragDepth = farNear[0];
		FragColor = vec4(0.);
		return ;
	}
	s_light light;
	light.pos = u_lightPos;
	light.colorLight = vec3(1.0, 1.0, 1.0);
	light.intensity = 1.;
		
	vec3 color = calculateColor(light, eye, worldDir, posHit, norm, dt.y);

	float	p10 = projection[2].z;
	float	p11 = projection[3].z;
	float eyeHitZ  = -dt.x * dot(worldDir, (vec3(0.,0.,-1.) * mat3(view)));
	float ndcDepth = -p10 + -p11 / eyeHitZ;
	// from [-1,1] to [0,1]
	float dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	gl_FragDepth = dep;

	FragColor = vec4(color, 1.0);
}