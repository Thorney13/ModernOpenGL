#pragma once
#include "core/window.h"
#include "scene/camera.h"
#include "scene/scene.h"

class InputManager {
private:
	Window* window;
	Camera* camera;
	Scene* scene;

	bool firstMouse;
	bool rightMousePressed;
	double lastX, lastY;
	float deltaTime;

	static InputManager* instance;

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	InputManager();
	~InputManager();

	void initialise(Window* window, Camera* camera, Scene* scene);

	void processInput(float deltaTime);

	void handleMouseButton(int button, int action, int mods);
	void handleCursorPosition(double xpos, double ypos);
	void handleScroll(double xoffset, double yoffset);
	void handleKey(int key, int action);
};