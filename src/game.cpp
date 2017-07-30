#include "game.hpp"
#include "gl/shader_program.hpp"
#include <iostream>

namespace hiraeth {

game::game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window_ptr = std::make_unique<engine::window>("hiraeth", 800, 600);
}

game::~game()
{
	SDL_Quit();
}

void game::loop()
{
	m_window_ptr->key_sig().connect([this](SDL_KeyboardEvent &e) {
		if (e.type == SDL_KEYUP && e.keysym.scancode == SDL_SCANCODE_Q) {
			m_window_ptr->close();	
		}
	});	

	float vertices[] = {
		-0.5f, -0.5f, 1.0f,
		 0.5f, -0.5f, 1.0f,
		 0.0f,  0.5f, 1.0f
	};
	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	gl::shader_program prog("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");

	while (!m_window_ptr->should_quit()) {
		m_window_ptr->update();

		glClearColor(0.1f, 0.1f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		prog.use();
		glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		m_window_ptr->render();
	}
}

game &game::instance()
{
	static game game;
	return game;
}

} // namespace hiraeth
