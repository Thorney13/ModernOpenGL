#include "cameraUtils.h"
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 getViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

float deltaTime = 0.0f;
float lastFrame = 0.0f; // Time of last frame

float fov = glm::radians(45.0f); // Field of view in radians
float nearPlane = 0.1f; // Near clipping plane
float farPlane = 100.0f; // Far clipping plane