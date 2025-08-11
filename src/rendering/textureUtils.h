#pragma once
#include "utils/glIncludes.h"
#include <string>

class Texture {
private:
	GLuint ID;
	int width, height, channels;
	bool loaded;

public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int textureUnit = 0) const;
	GLuint getID() const { return ID; }

	bool isLoaded() const { return loaded; }

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	static Texture createFallback();
};
