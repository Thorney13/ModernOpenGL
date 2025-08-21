#include "TimeManager.h"
#include "../utils/glIncludes.h"

void TimeManager::update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    totalTime = currentFrame;
}