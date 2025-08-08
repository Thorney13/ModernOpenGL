#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint loadTexture(const std::string& path);
GLuint createFallbackTexture();
