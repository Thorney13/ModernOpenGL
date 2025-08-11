#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

uniform float u_State;

void main()
{
    FragColor = vec4(vertexColor * u_State, 1.0);
}