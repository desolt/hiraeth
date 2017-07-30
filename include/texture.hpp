#ifndef GL_TEXTURE_HPP_
#define GL_TEXTURE_HPP_

#include <glad/glad.h>

namespace gl {

class texture {
public:
	texture(const std::string &path);

	void bind();

	GLuint id()  const noexcept;
	int width()  const noexcept;
	int height() const noexcept;
private:
	GLuint m_id;
	int m_width, int m_height;
};

} // namespace gl

#endif // GL_TEXTURE_HPP_
