#pragma once

class RectValues
{
public:

	int width;
	int height;
	int xPos;
	int yPos;

	RectValues();

	RectValues(int w, int h, int x, int y);

	class SDL_Rect CreateRect();

	void NullifieValues();

	~RectValues();
};