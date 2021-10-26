#version 410 core

in vec3 position;
// layout(location = 0) out float fragDepth;

void main()
{
	gl_FragDepth = position.z;
	// gl_FragColor = vec4(vec3(1.), 1.0);
}
