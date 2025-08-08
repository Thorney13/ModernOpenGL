#include "inputUtils.h"
#include "cameraUtils.h"

#include <vector>
#include <iostream>


bool firstMouse = true;
bool rightMousePressed = false;
double lastX, lastY;

float yaw = -90.0f; // Yaw angle
float pitch = 0.0f; // Pitch angle
float sensitivity = 0.1f; // Mouse sensitivity

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightMousePressed = true;
        firstMouse = true; // Reset first mouse flag when right button is pressed
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide cursor and capture mouse movement
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightMousePressed = false;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Reset cursor mode
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!rightMousePressed) return; // Only process if right mouse button is pressed

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false; // Reset first mouse flag
        return;
    }

    float xoffset = float(xpos - lastX) * sensitivity;
    float yoffset = float(lastY - ypos) * sensitivity; // Invert y-axis for natural movement

    lastX = xpos;
    lastY = ypos;

    yaw += xoffset; // Update yaw based on mouse movement
    pitch += yoffset; // Update pitch based on mouse movement
    pitch = glm::clamp(pitch, -89.0f, 89.0f); // Clamp pitch to avoid gimbal lock

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction); // Update camera front vector

}

void processInput(GLFWwindow* window) {
    float cameraSpeed = 2.5f * deltaTime; // Speed of camera movement

    // Forward / Back
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraFront * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraFront * cameraSpeed;

    // Left / Right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // Up / Down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= cameraUp * cameraSpeed;
}