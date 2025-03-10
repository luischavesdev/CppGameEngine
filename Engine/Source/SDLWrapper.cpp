#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(Uint32 flags) throw(InitError)
{
	if (SDL_Init(flags) != 0)
	{
		throw InitError();
	}
}

SDLWrapper::~SDLWrapper()
{
	SDL_Quit();
}
