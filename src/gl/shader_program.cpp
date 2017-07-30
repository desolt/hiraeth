#include "gl/shader_program.hpp"
#include <fstream>
#include <stdexcept>
#include <sstream>
#ifndef NDEBUG
#include <iostream>
#endif

namespace gl {

shader_program::shader_program(const std::string &vert_path,
	                           const std::string &frag_path)
{
	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	compile_shader(vert_shader, vert_path);
	compile_shader(frag_shader, frag_path);

	m_id = glCreateProgram();
	glAttachShader(m_id, vert_shader);
	glAttachShader(m_id, frag_shader);

	glLinkProgram(m_id);
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
}

shader_program::~shader_program()
{
	glDeleteProgram(m_id);
}

void shader_program::use() const
{
	glUseProgram(m_id);
}

GLuint shader_program::id() const noexcept
{
	return m_id;
}

void shader_program::compile_shader(GLuint shader, const std::string &src_path)
{
	// read from the file
	std::ifstream src_file;
	src_file.open(src_path);
	std::stringstream src_stream;
	src_stream << src_file.rdbuf();
	src_file.close();
	std::string src = src_stream.str();

	const char *src_c_str = src.c_str();
	glShaderSource(shader, 1, &src_c_str, nullptr);
	glCompileShader(shader);
	
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifndef NDEBUG
		constexpr std::size_t MAX_LOG_SIZE = 512;
		char err_log[MAX_LOG_SIZE];
		glGetShaderInfoLog(shader, MAX_LOG_SIZE, nullptr, err_log);
		std::cerr << "error compiling shader: " << err_log << std::endl;
#endif
		throw std::runtime_error("could not compile shader!");
	}
}

} // namespace gl
