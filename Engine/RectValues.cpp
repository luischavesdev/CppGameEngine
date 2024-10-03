#include "RectValues.h"
#include <SDL.h>

RectValues::RectValues()
{
	width = 0;
	height = 0;
	xPos = 0;
	yPos = 0;
}

RectValues::RectValues(int w, int h, int x, int y)
{
	width = w;
	height = h;
	xPos = x;
	yPos = y;
}

SDL_Rect RectValues::CreateRect()
{
	SDL_Rect tempRect;
	tempRect.w = width;
	tempRect.h = height;
	tempRect.x = xPos;
	tempRect.y = yPos;

	return tempRect;
}

void RectValues::NullifieValues()
{
	width = 0;
	height = 0;
	xPos = 0;
	yPos = 0;
}

RectValues::~RectValues()
{

}
