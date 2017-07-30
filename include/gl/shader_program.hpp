#ifndef GL_SHADER_PROGRAM_HPP_
#define GL_SHADER_PROGRAM_HPP_

#include <string>
#include <glad/glad.h>

namespace gl {

class shader_program {
public:
	shader_program(const std::string &vert_path,
	               const std::string &frag_path);
	~shader_program();

	void use() const;

	GLuint id() const noexcept;
private:
	GLuint m_id;

	static void compile_shader(GLuint shader, const std::string &src_path);
};

} // namespace gl

#endif // GL_SHADER_PROGRAM_HPP_
