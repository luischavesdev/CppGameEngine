#pragma once
#include <SDL.h>
#include <string>

class Window
{
private:
	SDL_Window* window;
	SDL_GLContext contextSDL;

public:
	Window(std::string title, int windowWidth, int windowHeight, bool fullscreen);

	SDL_Surface* GetSurface();

	void UpdateSurface();

	SDL_Window* GetSDLWindow();

	~Window();
};

