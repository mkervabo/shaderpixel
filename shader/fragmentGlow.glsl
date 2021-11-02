#version 410 core

out vec4 fragColor;

uniform vec2	u_resolution;
uniform float	u_fov;
uniform vec3	eye;
uniform mat4	inverseView;

#define MAX_DIST 500.0

vec3 ball1;
vec3 radii;

float unionSDF(float d1, float d2)
{
	return min(d1,d2);
}

float subtractionSDF(float d1, float d2)
{ 
	return max(-d1,d2); 
}

vec3 opCheapBend(in vec3 p)
{
	const float k = 10.0; // or some other amount
	float c = cos(k*p.x);
	float s = sin(k*p.x);
	mat2  m = mat2(c, -s, s, c);
	vec3  q = vec3(m * p.xy, p.z);
	return q;
}

float cylinderSDF(vec3 p, vec3 a, vec3 b, float r)
{
	vec3  ba = b - a;
	vec3  pa = p - a;
	float dotba = dot(ba, ba);
	float dotpba = dot(pa, ba);
	float x = length(pa * dotba - ba * dotpba) - r * dotba;
	float y = abs(dotpba - dotba * 0.5) - dotba * 0.5;
	float x2 = x * x;
	float y2 = y * y * dotba;
	float dist = (max(x, y) < 0.0) ? - min(x2, y2):(((x > 0.0) ? x2 : 0.0) + ((y > 0.0) ? y2 : 0.0));
		
	return (sign(dist) * sqrt(abs(dist)) / dotba);
}

float sphereSDF(in vec3 pt, in vec3 pos) {
	return (length(pt - pos) - radii.z);
}

float mushroomSDF(in vec3 pt, in vec3 pos, in float neg)
{
	float test =  sphereSDF(pt, pos);
	pt.z += 0.1;
	float test2 = sphereSDF(pt, pos);
	float sub = subtractionSDF(test2, test);
	pt.z -= 0.1;
	float uni = unionSDF(sub, cylinderSDF(pt, pos, vec3(0., 0., neg * 90.), 0.1));
	return uni;
}

float planeSDF( vec3 p, vec3 n, float h )
{
  // n must be normalized
  return dot(p, n) + h;
}

float DE(in vec3 z, in vec3 pt, in float neg)
{
  z.xy = mod((z.xy), 1.0) - vec2(0.5); // instance on xy-plane
  return mushroomSDF(pt, z, neg);
}

vec3 sdfs(in vec3 pt, in vec3 pos)
{
	return vec3(DE(pos, pt, 1.), DE(pt, pos, -1.), DE(pos, pt, 1.));
}


float sdf(in vec3 pt) {
	return (length(pt) - 2.0);
}

float min_comp(in vec3 comps) {
	return min(comps.x, min(comps.y, comps.z));
}

vec3 sdf_grad(in vec3 pt) {
	float f = sdf(pt);
	const float h = 0.001;
	const float h_inv = 1000.0;
		
	return vec3(sdf(pt + vec3(h, 0.0, 0.0)) - f,
				sdf(pt + vec3(0.0, h, 0.0)) - f,
				sdf(pt + vec3(0.0, 0.0, h)) - f);
}

float raymarch(in vec3 orig, in vec3 dir, out vec3 integral)
{
	vec3 pos = ball1;

	integral = vec3(0.0);
	float curr = 0.0;
	const float step_ratio = 0.25;

	vec3 curr_sdf = sdfs(orig, pos);
	float dist = step_ratio * min_comp(curr_sdf);
	vec3 next_sdf = sdfs(orig + dir * dist, pos);
	// integral from 0 to d of 1/(a+bx) =
	// screw it, just average some things.
	integral = dist * (0.25 / curr_sdf + 1.0 / (curr_sdf + next_sdf) + 0.25 / next_sdf);
	float total_dist = dist;
	const vec3 thresh = vec3(0.004);
	for (int i = 0; i < 128; ++i) {
		curr_sdf = next_sdf;
		dist = step_ratio * min_comp(curr_sdf);
		total_dist += dist;
		next_sdf = sdfs(orig + total_dist * dir, pos);
		vec3 mid = 0.5 * (curr_sdf + next_sdf);
		integral += dist * (0.5 / max(thresh, curr_sdf) + 
							0.3 / max(thresh, mid ) + 
							0. / max(thresh, next_sdf));

		if (min_comp(next_sdf) < 1.0e-3 || total_dist > MAX_DIST) {
			return total_dist;
		}
	}
	return total_dist;
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

mat3	rotateX(float theta)
{
	return mat3(vec3(1., 0., 0.),
			vec3(0., cos(theta), -sin(theta)),
			vec3(0., sin(theta), cos(theta)));
}

void main()
{
	// Normalized pixel coordinates (from 0 to 1)
	vec3 orig = eye - vec3(0., 0.5, 0.);
	vec3 dir = calculateMarchinDir(u_fov, u_resolution, gl_FragCoord.xy);

	dir = (inverseView * vec4(dir, 0.0)).xyz;

	mat3 tilt = rotateX(radians(90.));
	orig = tilt * orig;
	dir = tilt * dir;
	float rad = 0.6;
	ball1 = vec3(0.0, 0.0, 0.0);
	vec3 integral;
	radii = vec3(0.3);
	float raydist = raymarch(orig, dir, integral);
	vec3 col = smoothstep(0.15 * radii, vec3(0., 0., 0.), 0.45/(integral)); 
	if (raydist < MAX_DIST) {
		vec3 pt = orig + raydist * dir;
		vec3 norm = normalize(sdf_grad(pt));
		vec3 bounce = normalize(reflect(dir, norm));
	}
		
	// Output to screen
	fragColor = vec4(col,1.0);
}