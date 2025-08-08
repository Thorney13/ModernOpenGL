#pragma once
#include <string>
#include <glad/glad.h>

GLuint loadTexture(const std::string& path);
GLuint createFallbackTexture();
