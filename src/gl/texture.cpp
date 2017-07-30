#include "gl/texture.hpp"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace gl {

texture::texture(const std::string &path) : m_id(0), m_width(0), m_height(0)
{
	int channels;
	unsigned char *img = stbi_load(path.c_str(), &m_width, &m_height, &channels, 0);
	if (img == nullptr) {
		throw std::runtime_error("gl: could not find texture path");
	}

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img);
}

void texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

GLuint texture::id() const noexcept
{
	return m_id;
}

int texture::width() const noexcept
{
	return m_width;
}

int texture::height() const noexcept
{
	return m_height;
}

} // namespace gl
