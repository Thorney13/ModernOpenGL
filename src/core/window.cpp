#include "window.h"
#include "iostream"

Window::Window(int width, int height, const std::string& title) 
	: window(nullptr), width(width), height(height), title(title)
{

}

Window::~Window() {
	if (window) {
		glfwDestroyWindow(window);
		window = nullptr;
	}
	glfwTerminate();
}

bool Window::initialise() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
		auto* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
		if (self->resizeCallback) {
			self->resizeCallback(w, h);
		}
	});

	glfwSwapInterval(0);
	return true;
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

void Window::pollEvents() {
	glfwPollEvents();
}

void Window::setResizeCallback(const std::function<void(int, int)>& callback)
{
	resizeCallback = callback;
}

void Window::setKeyCallback(GLFWkeyfun callback) {
	glfwSetKeyCallback(window, callback);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun callback) {
	glfwSetMouseButtonCallback(window, callback);
}

void Window::setCursorPosCallback(GLFWcursorposfun callback) {
	glfwSetCursorPosCallback(window, callback);
}

void Window::setScrollCallback(GLFWscrollfun callback)
{
	glfwSetScrollCallback(window, callback);
}