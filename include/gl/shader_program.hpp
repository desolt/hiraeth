#ifndef HIRAETH_GL_SHADER_PROGRAM_HPP
#define HIRAETH_GL_SHADER_PROGRAM_HPP

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace gl {

    class shader_program {
    public:
        shader_program(const std::string &vert_shader, const std::string &frag_shader);
        ~shader_program();

        GLuint handle() const noexcept;

        void use();

        void set_mat4(const std::string &name, const glm::mat4 &matrix);

    private:
        GLuint m_handle;

        GLuint get_uniform_location(const std::string &name);
        static void compile_shader(GLuint shader, const std::string &path);
    };

} // namespace gl

#endif //HIRAETH_GL_SHADER_PROGRAM_HPP
