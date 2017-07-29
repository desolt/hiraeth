#include <glad/glad.h>
#include <SDL2/SDL.h>

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window *win = SDL_CreateWindow("Hello, world!", 
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			800, 600,
			SDL_WINDOW_OPENGL);
	if (win == nullptr)
		return 1;

	SDL_GLContext context = SDL_GL_CreateContext(win);
	if (!context)
		return 1;
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		return 1;

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
			}
		}

		glClearColor(0.1f, 0.1f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(win);
	}

	SDL_Delay(1000);
	SDL_DestroyWindow(win);

	SDL_Quit();
	return 0;
}
