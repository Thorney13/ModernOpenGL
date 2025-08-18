#include "inputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
	: window(nullptr), camera(nullptr), firstMouse(false), rightMousePressed(false),
	lastX(0), lastY(0), deltaTime(0)
{
    instance = this;
}

InputManager::~InputManager() {
    instance = nullptr;
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (instance) {
        instance->handleMouseButton(button, action, mods);
    }
}

void InputManager::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (instance) {
        instance->handleCursorPosition(xpos, ypos);
    }
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (instance) {
        instance->handleScroll(xoffset, yoffset);
    }
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (instance) {
        instance->handleKey(key, action);
    }
}

void InputManager::initialise(Window* window, Camera* camera)
{
    this->window = window;
    this->camera = camera;

    window->setMouseButtonCallback(mouseButtonCallback);
    window->setCursorPosCallback(cursorPositionCallback);
    window->setScrollCallback(scrollCallback);
    window->setKeyCallback(keyCallback);
}

void InputManager::processInput(float deltaTime) {
    this->deltaTime = deltaTime;

    // Process continuous keyboard input (optional, can be handled by key callback)
    GLFWwindow* glfwWindow = window->getGLFWWindow();
    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboardInput(Camera::FORWARD, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboardInput(Camera::BACKWARD, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboardInput(Camera::LEFT, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboardInput(Camera::RIGHT, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_E) == GLFW_PRESS)
        camera->processKeyboardInput(Camera::UP, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS)
        camera->processKeyboardInput(Camera::DOWN, deltaTime);
}

void InputManager::handleMouseButton(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightMousePressed = true;
        firstMouse = true;
        glfwSetInputMode(window->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightMousePressed = false;
        glfwSetInputMode(window->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void InputManager::handleCursorPosition(double xpos, double ypos) {
    if (!rightMousePressed) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    float xoffset = float(xpos - lastX);
    float yoffset = float(lastY - ypos);

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset, true);
}

void InputManager::handleScroll(double xoffset, double yoffset) {
    camera->processMouseScroll(float(yoffset));
}

void InputManager::handleKey(int key, int action) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        window->setShouldClose(true);
    }
}


