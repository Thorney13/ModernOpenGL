#version 330 core

in vec2 UV;
in vec3 vertexColor;
out vec4 fragColor;

uniform sampler2D u_Texture;

void main() {
	fragColor = vec4(texture(u_Texture, UV).rgb, 1.0f);
	//fragColor *= vec4(vertexColor, 1.0f);
}