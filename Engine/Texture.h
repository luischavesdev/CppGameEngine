#pragma once

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
	const char* textPath;
	unsigned int myTexture;
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

	TextDimensions GetTextureDimensions();

	FrameDimensions GetFrameDimensions();

	int GetLines();

	int GetColumns();

	~Texture();
};


