#version 410 core

layout(location = 0) out vec4 fragColor;
layout(location = 1) out float fragDepth;

void main()
{
	fragDepth = gl_FragDepth;
	fragColor = vec4(vec3(1.), 1.0);
}
