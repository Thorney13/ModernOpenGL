#version 330 core

in vec2 UV;
in vec3 vertexColor;
out vec4 fragColor;


uniform float iTime;
uniform vec2 iResolution; 
uniform vec3 camPos;
uniform vec3 camTarget;

// Constants
const int MAX_STEPS = 128;
const float MAX_DIST = 100.0;
const float EPSILON = 0.001;

// SDF function
//vec3 spherePos = vec3(sin(iTime), 0.0, cos(iTime));
float sceneSDF(vec3 p) {
    return length(p - vec3(1.0, 0.0, 0.0)) - 1.0;
}

// Normal estimation
vec3 estimateNormal(vec3 p) {
    const float eps = 0.001;
    return normalize(vec3(
        sceneSDF(p + vec3(eps, 0.0, 0.0)) - sceneSDF(p - vec3(eps, 0.0, 0.0)),
        sceneSDF(p + vec3(0.0, eps, 0.0)) - sceneSDF(p - vec3(0.0, eps, 0.0)),
        sceneSDF(p + vec3(0.0, 0.0, eps)) - sceneSDF(p - vec3(0.0, 0.0, eps))
    ));
}

void main() {
    vec2 uv = (UV * 2.0 - 1.0) * vec2(iResolution.x / iResolution.y, 1.0);

    vec3 forward = normalize(camTarget);
    vec3 right = normalize(cross(vec3(0.0, 1.0, 0.0), forward));
    vec3 up = cross(forward, right);

    vec3 rayDir = normalize(forward + uv.x * right + uv.y * up);
    vec3 rayOrigin = camPos;

    float totalDist = 0.0;
    bool hit = false;
    vec3 p;

    for (int i = 0; i < MAX_STEPS; ++i) {
        p = rayOrigin + rayDir * totalDist;
        float dist = sceneSDF(p);

        if (dist < EPSILON) {
            hit = true;
            break;
        }

        totalDist += dist;
        if (totalDist > MAX_DIST) break;
    }

    vec3 color = vec3(0.0);
    if (hit) {
        vec3 normal = estimateNormal(p);
        vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
        float diff = max(dot(normal, lightDir), 0.0);
        color = vec3(diff);
    }

    fragColor = vec4(color, 1.0);

}