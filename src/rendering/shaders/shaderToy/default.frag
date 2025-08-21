#version 330 core

in vec2 UV;
in vec3 vertexColor;
out vec4 fragColor;


uniform float iTime;
uniform vec2 iResolution; 

void main()
{
    vec2 uv = UV;
    
    // Convert to ShaderToy's coordinates (from -1 to 1)
    //uv = uv * 2.0 - 1.0;
    uv = uv;
    
    vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0, 2, 4));
    
    fragColor = vec4(uv.x, uv.y, 0.0, 1.0);
}