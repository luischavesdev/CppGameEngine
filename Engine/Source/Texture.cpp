#include "glad.h"
#include "stb_image.h"

#include "Texture.h"
#include "Logger.h"

Texture::Texture(const char* filePath, int linesRef, int columnsRef)
{
	SetTexture(filePath, columnsRef, linesRef);
}

void Texture::SetTexture(const char* filePath, int columnsRef, int linesRef)
{
	textPath = filePath;
	lines = linesRef;
	columns = columnsRef;

	glGenTextures(1, &myTexture);
	glActiveTexture(GL_TEXTURE0 + myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	//loading the texture
	int nrChannels;
	unsigned char* data = stbi_load(filePath, &myTextDimensions.width, &myTextDimensions.height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myTextDimensions.width, myTextDimensions.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		CUSTOM_LOGGER("ERROR: Failed to load texture");
	}
	stbi_image_free(data);

	myFrameDimensions.width = myTextDimensions.width / columns;
	myFrameDimensions.height = myTextDimensions.height / lines;
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, myTexture);
}

// --- || Getters || ---

unsigned int Texture::GetTexture()
{
	return myTexture;	
}

std::string Texture::GetTextName()
{
	return textPath;
}

int Texture::GetLines()
{
	return lines;
}

int Texture::GetColumns()
{
	return columns;
}

Texture::TextDimensions Texture::GetTextureDimensions()
{
	return myTextDimensions;
}

Texture::FrameDimensions Texture::GetFrameDimensions()
{
	return myFrameDimensions;
}

// --- || Destructor || ---

Texture::~Texture()
{
	textPath = nullptr;
}
