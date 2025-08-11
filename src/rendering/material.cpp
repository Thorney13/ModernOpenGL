#include "material.h"

Material::Material(Shader* shader)
	: shader(shader) {
}

void Material::addTexture(const std::string& uniformName, const Texture& texture) {
	textures[uniformName] = texture;
}

void Material::use() const {
	if (!shader) return;

	shader->use();
	int textureUnit = 0;
	for (const auto& [uniformName, texture] : textures) {
		texture.bind(textureUnit);
		shader->setInt(uniformName, textureUnit);
		textureUnit++;
	}
}

void Material::setMVP(const glm::mat4& mvp) {
	if (shader) {
		shader->setMat4("mvp", mvp);
	}
}