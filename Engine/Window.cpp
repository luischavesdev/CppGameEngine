#include <iostream>
#include "Window.h"
#include "InitError.h"
#include "glad.h"

Window::Window(std::string title, int windowWidth, int windowHeight, bool fullscreen)
{
	if (fullscreen)
	{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth,
			windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

	}
	else
	{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth,
			windowHeight, SDL_WINDOW_OPENGL);
	}

	if (window == nullptr)
	{
		throw InitError();
	}
	else
	{
		contextSDL = SDL_GL_CreateContext(window);
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			SDL_Quit();
		}
	}
}

SDL_Surface* Window::GetSurface()
{
	return SDL_GetWindowSurface(window);
}

void Window::UpdateSurface()
{
	//std::cout << "update" << std::endl;
	SDL_UpdateWindowSurface(window);
}

SDL_Window* Window::GetSDLWindow()
{
	return window;
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(contextSDL);
}