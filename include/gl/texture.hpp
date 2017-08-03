#ifndef HIRAETH_GL_TEXTURE_HPP
#define HIRAETH_GL_TEXTURE_HPP

#include <string>
#include <glad/glad.h>

namespace gl {

    class texture {
    public:
        texture(const std::string &path);
        ~texture();

        int get_width() const;
        int get_height() const;

        void bind();

    private:
        GLuint m_handle;
        int m_width, m_height;
    };

} // namespace gl

#endif //HIRAETH_GL_TEXTURE_HPP
