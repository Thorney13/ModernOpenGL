// cameraUtils.h
#pragma once
#include <glm/glm.hpp>

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

glm::mat4 getViewMatrix();

extern float deltaTime;
extern float lastFrame;

extern float fov;
extern float nearPlane;
extern float farPlane;