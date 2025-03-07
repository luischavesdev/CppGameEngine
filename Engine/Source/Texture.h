#pragma once
#include <string>

class Texture 
{
public:
	struct TextDimensions
	{
		int width;
		int height;
	};

	struct FrameDimensions
	{
		int width;
		int height;
	};


private:
	unsigned int myTexture;
	const char* textPath;
	int lines;
	int columns;

	TextDimensions myTextDimensions;
	FrameDimensions myFrameDimensions;


public:
	Texture(const char* filePath, int linesRef, int columnsRef);

	void SetTexture(const char* filePath, int columnsRef, int linesRef);
	void BindTexture();

	unsigned int GetTexture();
	std::string GetTextName();
	int GetLines();
	int GetColumns();
	TextDimensions GetTextureDimensions();
	FrameDimensions GetFrameDimensions();
	
	~Texture();
};
