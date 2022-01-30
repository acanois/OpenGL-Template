#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2, aTexCoord; // 2D

out vec3 texColor;
out vec2 TexCoord; // 2D

void main() {
	gl_Position = vec4(aPos, 1.0);
	texColor = aColor;
	TexCoord = aTexCoord;
}