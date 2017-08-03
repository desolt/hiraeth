#include "gl/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>

namespace gl {

    texture::texture(const std::string &path)
    {
        int channels;
        unsigned char *img = stbi_load(path.c_str(), &m_width, &m_height, &channels, 0);
        if (img == nullptr)
            throw std::runtime_error("gl: could not load texture with path " + path);

        GLuint img_type = GL_RGB;
        if (channels == 4)
            img_type = GL_RGBA;

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &m_handle);
        glBindTexture(GL_TEXTURE_2D, m_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, img_type, m_width, m_height, 0, img_type, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(img);
    }

    texture::~texture()
    {
        glDeleteTextures(1, &m_handle);
    }

    int texture::get_width() const
    {
        return m_width;
    }

    int texture::get_height() const
    {
        return m_height;
    }

    void texture::bind()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_handle);
    }

} // namespace gl
