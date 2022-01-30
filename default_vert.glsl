#version 460 core

// Input with attribute position 0
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(0.4, 0.3, 0.7, 1.0);
}