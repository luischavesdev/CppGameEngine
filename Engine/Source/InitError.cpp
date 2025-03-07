#include "SDL.h"

#include "InitError.h"

InitError::InitError() :exception(), msg(SDL_GetError()) 
{

}

InitError::InitError(const std::string& m) : exception(), msg(m) 
{

}

const char* InitError::what() const throw() 
{
	return msg.c_str();
}

InitError::~InitError() throw() 
{

}
