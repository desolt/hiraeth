#include "engine/window.hpp"
#include <stdexcept>

namespace hiraeth {
namespace engine {

window::window(const std::string &title, int width, int height)
	: m_width(width), m_height(height)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_handle = SDL_CreateWindow(title.c_str(), 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height,
			SDL_WINDOW_OPENGL);
	if (m_handle == nullptr)
		throw std::runtime_error("engine: could not create window.");

	m_context = SDL_GL_CreateContext(m_handle);
	if (!m_context)
		throw std::runtime_error("engine: could not create an OpenGL context.");
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		throw std::runtime_error("engine: could not load glad.");
	glViewport(0, 0, width, height);
}

window::~window()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_handle);
}

bool window::should_quit() const noexcept
{
	return m_should_quit;
}

void window::close() noexcept
{
	m_should_quit = true;
}

void window::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			m_key_sig(event.key);
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				glViewport(0, 0, event.window.data1, event.window.data2);
				m_resize_sig(event.window.data1, event.window.data2);
			}
			break;
		case SDL_QUIT:
			m_should_quit = true;
			break;
		}
	}
}

void window::render()
{
	SDL_GL_SwapWindow(m_handle);
}

boost::signals2::signal<void (SDL_KeyboardEvent &)> &window::key_sig() noexcept
{
	return m_key_sig;
}

boost::signals2::signal<void (int, int)> &window::resize_sig() noexcept
{
	return m_resize_sig;
}


} // namespace engine
} // namespace hiraeth
