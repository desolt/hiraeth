#ifndef ENGINE_WINDOW_HPP_
#define ENGINE_WINDOW_HPP_

#include <string>
#include <boost/signals2.hpp>
#include <glad/glad.h> // must be before any other gl using header
#include <SDL2/SDL.h>

namespace hiraeth {
namespace engine {

class window {
public:
	window(const std::string &title, int width, int height);
	virtual ~window();

	bool should_quit() const noexcept;

	void close() noexcept;
	void update();
	void render();

	boost::signals2::signal<void (SDL_KeyboardEvent &)> &key_sig() noexcept;
	boost::signals2::signal<void (int, int)> &resize_sig() noexcept;
private:
	SDL_Window *m_handle;
	SDL_GLContext m_context;
	
	int m_width, m_height;
	bool m_should_quit = false;

	boost::signals2::signal<void (SDL_KeyboardEvent &)> m_key_sig;
	boost::signals2::signal<void (int, int)> m_resize_sig;
};

} // namespace engine
} // namespace hiraeth

#endif // ENGINE_WINDOW_HPP_
