#version 330 core

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;


// Main fragment shader
void main() {
    
    float ambientStrength = 0.1;
    vec3 ambient = lightColor * ambientStrength;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos); 

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

    fragColor = vec4(result, 1.0);
}