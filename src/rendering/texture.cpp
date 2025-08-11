#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& path)
	: ID(0), width(0), height(0), channels(0), loaded(false)
    {

    // Load image data
    stbi_set_flip_vertically_on_load(true); // OpenGL expects textures to be flipped
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data) {
        std::cout << "Successfully loaded texture: " << path << std::endl;
        std::cout << "Dimensions: " << width << "x" << height << ", Channels: " << channels << std::endl;

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        // Determine format based on number of channels
        GLenum format;
        GLenum internalFormat;
        switch (channels) {
        case 1:
            format = GL_RED;
            internalFormat = GL_R8;
            break;
        case 3:
            format = GL_RGB;
            internalFormat = GL_RGB8;
            break;
        case 4:
            format = GL_RGBA;
            internalFormat = GL_RGBA8;
            break;
        default:
            std::cerr << "Unsupported number of channels: " << channels << std::endl;
            stbi_image_free(data);
            return;
        }

        // Upload texture data
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // Generate mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Clean up
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
		loaded = true;

        std::cout << "Texture created with ID: " << ID << std::endl;
    }
    else {
        std::cerr << "Failed to load texture: " << path << std::endl;
        std::cerr << "STB Error: " << stbi_failure_reason() << std::endl;
    }
 }

Texture::Texture() : ID(0), width(0), height(0), channels(0), loaded(false) {

}

Texture::~Texture() {
    if (ID != 0) {
        glDeleteTextures(1, &ID);
    }
}

void Texture::bind(unsigned int textureUnit) const {
    if (loaded) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, ID);
    } else {
        std::cerr << "Texture not loaded, cannot bind." << std::endl;
	}
}

Texture Texture::createFallback() {
    std::cerr << "Creating fallback checkerboard texture..." << std::endl;

    // Create a simple 2x2 checkerboard pattern
    unsigned char checkerboard[] = {
        255, 255, 255, 255,  // White
        0, 0, 0, 255,        // Black
        0, 0, 0, 255,        // Black  
        255, 255, 255, 255   // White
    };

	Texture fallbackTexture("");
    glGenTextures(1, &fallbackTexture.ID);
    glBindTexture(GL_TEXTURE_2D, fallbackTexture.ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    fallbackTexture.width = 2;
    fallbackTexture.height = 2;
    fallbackTexture.channels = 4;
    fallbackTexture.loaded = true;

    std::cout << "Fallback texture created with ID: " << fallbackTexture.ID << std::endl;
	return fallbackTexture;
}