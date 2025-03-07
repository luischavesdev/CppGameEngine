#pragma once
#include <string>
#include "SDL.h"

class Window
{
private:
	SDL_Window* window;
	SDL_GLContext contextSDL;


public:
	Window(std::string title, int windowWidth, int windowHeight, bool fullscreen);

	void UpdateSurface();

	SDL_Surface* GetSurface();
	SDL_Window* GetSDLWindow();

	~Window();
};
