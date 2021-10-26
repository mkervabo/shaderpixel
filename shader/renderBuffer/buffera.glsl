#version 410 core

in vec3 position;
// layout(location = 0) out float fragDepth;

out vec4 fragColor;

void main()
{
	fragColor = vec4(vec3(1.), 1.0);
}
