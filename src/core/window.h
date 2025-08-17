#pragma once
#include "utils/glIncludes.h"
#include <string>
#include <functional>

class Window {
private:
	GLFWwindow* window;
	int width, height;
	std::string title;
	std::function<void(int, int)> resizeCallback;

public:
	Window(int width, int height, const std::string& title);
	~Window();

	bool initialise();
	bool shouldClose();
	void swapBuffers();
	void pollEvents();

	void setShouldClose(bool value) { glfwSetWindowShouldClose(window, value); }
	void setResizeCallback(const std::function<void(int, int)>& callback);
	void setKeyCallback(GLFWkeyfun callback);
	void setMouseButtonCallback(GLFWmousebuttonfun callback);
	void setCursorPosCallback(GLFWcursorposfun callback);
	void setScrollCallback(GLFWscrollfun callback);

	GLFWwindow* getGLFWWindow() const { return window; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
};