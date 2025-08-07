#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

uniform int u_State;

void main() {
    if (u_State == 1)
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red
    else
        FragColor = vec4(0.0, 0.0, 1.0, 1.0); // Blue
   }