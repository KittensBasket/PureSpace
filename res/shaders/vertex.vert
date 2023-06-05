#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aOffset;

uniform float Size;

out vec2 TexCoord;

void main()
{
	float angle = aOffset.z;
	mat2 rot = mat2(vec2(cos(angle), sin(angle)), vec2(-sin(angle), cos(angle)));

	gl_Position = vec4(rot * (Size * aPos) + aOffset.xy, 0.0, 1.0);
	TexCoord = aTex;
}
