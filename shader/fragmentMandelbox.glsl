#version 410 core

// uniform float	time;
uniform vec2	u_resolution;
uniform mat4	inverseView;
uniform float	u_fov;
uniform mat4	view;
uniform vec3	eye;
uniform mat4	projection;
out vec4		fragColor;
uniform float	farNear[2];
uniform vec3	u_lightPos;


const int MAX_MARCHING_STEPS = 200;
// const float MIN_DIST = 0.0;
// const float MAX_DIST = 500.0;
const float EPSILON = 0.008;
const float MIN_RAD = 0.4;
const float FIXED_RAD = 2.0;
void sphereFold(inout vec3 z, inout float dz)
{
	float r2 = dot(z,z);
	if (r2 < MIN_RAD)
    { 
		float temp =  FIXED_RAD / MIN_RAD;
		z *= temp;
		dz *= temp;
	}
    else if (r2 <  FIXED_RAD)
    { 
		float temp =  FIXED_RAD / r2;
		z *= temp;
		dz *= temp;
	}
}

const float FOLDING_LIMIT = 1.0;
void boxFold(inout vec3 z, inout float dz)
{
	z = clamp(z, -FOLDING_LIMIT, FOLDING_LIMIT) * 2.0 - z;
}

const int ITERATIONS = 12;
float mandelboxSDF(vec3 z) {
    float scale = 2.0;
	vec3 offset = z;
	float dr = 1.0;
	for (int n = 0; n < ITERATIONS; n++)
    {
		boxFold(z,dr);          // Reflect
		sphereFold(z,dr);       // Sphere Inversion
        z = scale * z + offset; // Sphere Inversion
        dr = dr * abs(scale) + 1.0;
	}
	float r = length(z);
	return r / abs(dr);
}

float sceneSDF(vec3 samplePoint) {
    float mandelboxDist = mandelboxSDF(samplePoint / 0.25) * 0.25;
    return (mandelboxDist);
}


// eye: the eye point, acting as the origin of the ray
// marchingDirection: the normalized direction to march in
// start: the starting distance away from the eye
// end: the max distance away from the ey to march before giving up
float shortestDistanceToSurface(vec3 eye, vec3 marchingDirection, float start, float end) {
    float depth = start;
    for (int i = 0; i < MAX_MARCHING_STEPS; i++) {
        float dist = sceneSDF(eye + depth * marchingDirection);
        if (dist < EPSILON) {
			return depth;
        }
        depth += dist;
        if (depth >= end) {
            return end;
        }
    }
    return end;
}
            
// // fieldOfView: vertical field of view in degrees
// // size: resolution of the output image
// // fragCoord: the x,y coordinate of the pixel in the output image
// vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
//     vec2 xy = fragCoord - size / 2.0;
//     float z = size.y / tan(radians(fieldOfView) / 2.0);
//     return normalize(vec3(xy, -z));
// }

vec3 estimateNormal(vec3 p) {
    return normalize(vec3(
        sceneSDF(vec3(p.x + EPSILON, p.y, p.z)) - sceneSDF(vec3(p.x - EPSILON, p.y, p.z)),
        sceneSDF(vec3(p.x, p.y + EPSILON, p.z)) - sceneSDF(vec3(p.x, p.y - EPSILON, p.z)),
        sceneSDF(vec3(p.x, p.y, p.z  + EPSILON)) - sceneSDF(vec3(p.x, p.y, p.z - EPSILON))
    ));
}

vec3 phongContribForLight(vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye,
                          vec3 lightPos, vec3 lightIntensity) {
    vec3 N = estimateNormal(p);
    vec3 L = normalize(lightPos - p);
    vec3 V = normalize(eye - p);
    vec3 R = normalize(reflect(-L, N));
    
    float dotLN = dot(L, N);
    float dotRV = dot(R, V);
    
    if (dotLN < 0.0) {
        // Light not visible from this point on the surface
        return estimateNormal(p) * 0.1;
    } 
    
    if (dotRV < 0.0) {
        // Light reflection in opposite direction as viewer, apply only diffuse
        // component
        return lightIntensity * (k_d * dotLN);
    }
    return (k_d * dotLN + k_s * pow(dotRV, alpha));
}

// k_a: Ambient color
// k_d: Diffuse color
// k_s: Specular color
// alpha: Shininess coefficient
// p: position of point being lit
// eye: the position of the camera
vec3 phongIllumination(vec3 k_a, vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye) {
    const vec3 ambientLight = 0.5 * vec3(1.0, 1.0, 1.0);
    vec3 color = ambientLight * k_a;
    
    vec3 light1Pos =  u_lightPos;
    vec3 light1Intensity = vec3(0.1, 0.1, 0.1);
    
    color += phongContribForLight(k_d, k_s, alpha, p, eye,
                                  light1Pos,
                                  light1Intensity);
    
    // vec3 light2Pos = vec3(20.0 * sin(time),
    //                       40.0 * cos(time),
    //                       50.0);
    // vec3 light2Intensity = vec3(0.4, 0.4, 0.4);
    
    // color += phongContribForLight(k_d, k_s, alpha, p, eye,
    //                               light2Pos,
    //                               light2Intensity);    
    return color;
}

mat4 viewMatrixTest(vec3 eye, vec3 center, vec3 up) {
    vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);
    return mat4(
        vec4(s, 0.0),
        vec4(u, 0.0),
        vec4(-f, 0.0),
        vec4(0.0, 0.0, 0.0, 1)
    );
}

vec3	calculateMarchinDir(float fov, vec2 resolutionSize, vec2 fragCoord)
{

	// vec2 xy = fragCoord - resolutionSize / 2.0 ;
	// float z = resolutionSize.y / tan(radians(fov));
	// return (normalize(vec3(xy, -z)));

	float	ratio = resolutionSize.x / resolutionSize.y;
	vec2	xy = (fragCoord - 0.5) / resolutionSize;
	//from [0,1] to [-1, 1]
	xy.x = (2 * xy.x - 1) * ratio * tan(radians(fov / 1.));
	xy.y = (2 * xy.y - 1) * tan(radians(fov / 1.));
	return (normalize(vec3(xy, -1)));
}

void main()
{
	vec3	dir = calculateMarchinDir(u_fov, u_resolution, gl_FragCoord.xy / 2);
	vec3	worldDir = (inverseView * vec4(dir, 0.0)).xyz;
	float	dist = shortestDistanceToSurface(eye, worldDir, farNear[1], farNear[0]);
    
    if (dist > farNear[0] - EPSILON) {
        gl_FragDepth = farNear[0];
        fragColor = vec4(0.0, 0.0, 0.0, 0.0);
		return;
    }
    
    vec3 p = eye + dist * worldDir;
    
    vec3 K_a = vec3(0.2, 0.2, 0.2);
    vec3 K_d = estimateNormal(p);
    vec3 K_s = vec3(1.0, 1.0, 1.0);
    float shininess = 10.0;
    
    vec3 color = phongIllumination(K_a, K_d, K_s, shininess, p, eye);

    float	p10 = projection[2].z;
	float	p11 = projection[3].z;
	float eyeHitZ  = -dist * dot(worldDir, (vec3(0.,0.,-1.) * mat3(view)));
	float ndcDepth = -p10 + -p11 / eyeHitZ;
	// from [-1,1] to [0,1]
    float dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
    gl_FragDepth = dep;

    fragColor = vec4(color, 1.0);
}