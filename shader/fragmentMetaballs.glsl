#version 410 core

out vec4 fragColor;
uniform float metaSize;
uniform float metaVelocity;
uniform float metaMaxSize;
uniform float metaMinSize;
uniform int metaNbBalls;
float s[20];
const float EPSILON = 0.0025;

uniform float	time;
uniform vec2	u_resolution;
uniform float	u_fov;
uniform mat4	projection;
uniform mat4	view;
uniform vec3	eye;
uniform mat4	inverseView;
uniform float	farNear[2];


float sphere(vec3 pos, float rad) {
	float distanceFromCenter = length(pos);
	float sphereRadius = rad;
	return distanceFromCenter - sphereRadius;
}

float makeBlobs(float s1, float s2, float s3, float s4) {
	float k = -6.0;
	float blob = exp(k * s1) + exp(k * s2) + exp(k * s3) + exp(k * s4);
	return log(blob) / k; 
}

vec3 hash(float h)
{
	return fract(sin(vec3(h, h + 1.0, h + 2.0)) * vec3(43758.5453123,22578.1459123,19642.3490423));
}

float makeScene(vec3 pos, vec2 coord) {
	vec3 pos2 = pos;
	//float song = texture(iChannel0, vec2(coord.x / iResolution.x, 1)).x;
	for (int i = 0; i < metaNbBalls; i++)
	{
		float h = float(i) / 8.0;
		//pos2 = pos + VELOCOTY * vec3(cos(hash(h * 0.7) * hash(h * 0.6) * (time + song * 2.)));
		pos2 = pos + metaVelocity * vec3(cos(hash(h * 0.7) * hash(h * 0.6) * (time)));
		s[i] = sphere(pos2, clamp(h * metaSize, metaMinSize, metaMaxSize));
	}
	// MakeBlobs
	float k = -4.0;
	float blob = 0.0;
	for (int i = 0; i < metaNbBalls; i++)
	{
		blob += exp(k * s[i]);
	}
	return log(blob) / k;
}

float intersection( in vec3 camPos, in vec3 camDir, vec2 coord) {
	const float maxD = 20.0;
	const float precis = EPSILON;
	float h = precis;
	float t = 0.0;
	for( int i = 0; i < 90; i++ ) {
		if(h < precis || t > maxD) break;
		h = makeScene(camPos + camDir * t, vec2(1.));
		t += h;
	}
	if( t > maxD ) t = 0.0;
	return t;
}

vec3 calcNormal( in vec3 pos, vec2 coord) {
	const float eps = 0.1;
	const vec3 v1 = vec3( 1.0,-1.0,-1.0);
	const vec3 v2 = vec3(-1.0,-1.0, 1.0);
	const vec3 v3 = vec3(-1.0, 1.0,-1.0);
	const vec3 v4 = vec3( 1.0, 1.0, 1.0);
	return normalize( v1 * makeScene( pos + v1 * eps, coord ) + 
					v2 * makeScene( pos + v2 * eps, coord ) + 
					v3 * makeScene( pos + v3 * eps, coord ) + 
					v4 * makeScene( pos + v4 * eps, coord ) );

}

vec3 ambient(vec3 k_a) {
	const vec3 ambientLight = 1.0 * vec3(1.0, 1.0, 1.0);
	vec3 color = ambientLight * k_a;
	return color;
}

mat3 calcLookAtMatrix( in vec3 camPos, in vec3 camTar, in float roll ) {
	vec3 w = normalize(camTar - camPos);
	vec3 u = normalize(cross(w, vec3(sin(roll), cos(roll), 0.0)));
	vec3 v = normalize(cross(u, w));
	return mat3(u, v, w);
}

vec3 rotY(vec3 p, float theta)
{
	return (p * mat3(
		vec3(cos(theta), 0., sin(theta)),
		vec3(0., 1., 0.),
		vec3(-sin(theta), 0., cos(theta))));
}

vec3	calculateMarchinDir(float fov, vec2 resolutionSize, vec2 fragCoord)
{
	float	ratio = resolutionSize.x / resolutionSize.y;
	vec2	xy = (fragCoord - 0.5) / resolutionSize;
	//from [0,1] to [-1, 1]
	xy.x = (2 * xy.x - 1) * ratio * tan(radians(fov / 2.));
	xy.y = (2 * xy.y - 1) * tan(radians(fov / 2.));
	return (normalize(vec3(xy, -1)));
}

vec3 light(vec3 objColor, vec3 p) {
	const vec3 ambientLight = 0.1 * vec3(1.0, 1.0, 1.0);
	
	vec3 norm = calcNormal(p, vec2(1));
	vec3 lightPos =  vec3(0.0, 40.0, 45.0);
	vec3 lightDir = normalize(lightPos - p);
	float diffuseLight = max(dot(norm, lightDir), 0.0);
	
	vec3 color = (ambientLight + diffuseLight) * objColor;
	return color;
}

void main()
{
	vec3	dir = calculateMarchinDir(u_fov, u_resolution, gl_FragCoord.xy / 2);
	vec3	worldDir = (inverseView * vec4(dir, 0.0)).xyz;
	float	dist = intersection(eye, worldDir, gl_FragCoord.xy);
	
	if (dist > farNear[0] - EPSILON) {
		gl_FragDepth = farNear[0];
		fragColor = vec4(0.0, 0.0, 0.0, 0.0);
		return;
	}
	
	vec3 p = eye + dist * worldDir;	
	vec3 objColor = calcNormal(p, vec2(1));
	vec3 color = light(objColor, p);

	float	p10 = projection[2].z;
	float	p11 = projection[3].z;
	float eyeHitZ  = -dist * dot(worldDir, (vec3(0.,0.,-1.) * mat3(view)));
	float ndcDepth = -p10 + -p11 / eyeHitZ;
	// from [-1,1] to [0,1]
	float dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	gl_FragDepth = dep;

	fragColor = vec4(color, 1.0);
}