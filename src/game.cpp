#include "game.hpp"
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

	while (!m_window_ptr->should_quit()) {
		m_window_ptr->update();

		glClearColor(0.1f, 0.1f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		m_window_ptr->render();
	}
}

game &game::instance()
{
	static game game;
	return game;
}

} // namespace hiraeth
