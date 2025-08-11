#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 vertexUV;

uniform mat4 mvp;

out vec3 vertexColor;
out vec2 UV;    

void main() {
    gl_Position = mvp * vec4(aPos, 1.0);
    vertexColor = aColor;

    UV = vertexUV;
}