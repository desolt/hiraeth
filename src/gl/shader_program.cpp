#include "gl/shader_program.hpp"
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#ifndef NDEBUG
#include <iostream>
#endif

namespace gl {

    shader_program::shader_program(const std::string &vert_path, const std::string &frag_path)
    {
        GLuint vert = glCreateShader(GL_VERTEX_SHADER);
        GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

        compile_shader(vert, vert_path);
        compile_shader(frag, frag_path);

        m_handle = glCreateProgram();
        glAttachShader(m_handle, vert);
        glAttachShader(m_handle, frag);
        glLinkProgram(m_handle);

        // unneeded after linking
        glDeleteShader(vert);
        glDeleteShader(frag);
    }

    shader_program::~shader_program()
    {
        glDeleteProgram(m_handle);
    }

    GLuint shader_program::handle() const noexcept
    {
        return m_handle;
    }

    void shader_program::use()
    {
        glUseProgram(m_handle);
    }

    void shader_program::set_mat4(const std::string &name, const glm::mat4 &matrix)
    {
        glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    GLuint shader_program::get_uniform_location(const std::string &name)
    {
        glGetUniformLocation(m_handle, name.c_str());
    }

    void shader_program::compile_shader(GLuint shader, const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
            throw std::runtime_error("gl: shader path does not exist.");

        std::stringstream srcstream;
        srcstream << file.rdbuf();
        std::string src = srcstream.str();
        file.close();

        const char *src_c_str = src.c_str();
        glShaderSource(shader, 1, &src_c_str, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
#ifndef NDEBUG
            char err_log[512];
            glGetShaderInfoLog(shader, 512, nullptr, err_log);
            err_log[511] = '\0';
            std::cerr << "gl::shader_program: error compiling shader:\n" << err_log << std::endl;
#endif

            throw std::runtime_error("gl::shader_program: error compiling shader with path " + path);
        }
    }

} // namespace gl
