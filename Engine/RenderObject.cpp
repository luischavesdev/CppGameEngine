#include <iostream>
#include <iomanip>
#include <SDL.h>
#include "RenderObject.h"
#include "Texture.h"
#include "RectValues.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "GameEngine.h"
#include "glad.h"
#include "Vector2.h"

//STILL
RenderObject::RenderObject(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef) 
{
	layer = layerRef;
	id = idRef;
	myTexture = textureRef;
	myEngineRef = engineRef;

	colorOverlay.x = 1.0f;
	colorOverlay.y = 1.0f;
	colorOverlay.z = 1.0f;

	/* Vertices handling */
	textWidth = myTexture->GetTextureDimensions().width;
	textHeight = myTexture->GetTextureDimensions().height;
	halfWindowWidth = myEngineRef->GetWindowWidth() / 2.0f;
	halfWindowHeight = myEngineRef->GetWindowHeight() / 2.0f;
	vertexX = (halfWindowWidth - (halfWindowWidth - (textWidth / 2.0f))) / halfWindowWidth;
	vertexY = (halfWindowWidth - (halfWindowWidth - (textHeight / 2.0f))) / halfWindowWidth;


	/* Texture coordinates handling */
	bottomFrameVertice = 0.0f;
	topFrameVertice = 1.0f;
	rightFrameVertice = 1.0f;
	leftFrameVertice = 0.0f;

	/* Finally setting the vertices */
	RefreshVertices(0, 0);
}

//ANIMATED
RenderObject::RenderObject(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef, float playbackSpeedRef, int currentLineRef, 
	int currentColumnRef) 
{
	layer = layerRef;
	id = idRef;
	myTexture = textureRef;
	myEngineRef = engineRef;

	colorOverlay.x = 1.0f;
	colorOverlay.y = 1.0f;
	colorOverlay.z = 1.0f;

	animated = true;
	animationSpeed = playbackSpeedRef;

	/* Vertices handling */
	textWidth = myTexture->GetTextureDimensions().width;
	textHeight = myTexture->GetTextureDimensions().height;
	textureLines = myTexture->GetLines();
	textureColumns = myTexture->GetColumns();
	halfWindowWidth = myEngineRef->GetWindowWidth() / 2.0f;
	halfWindowHeight = myEngineRef->GetWindowHeight() / 2.0f;
	vertexX = ((halfWindowWidth - (halfWindowWidth - (textWidth / 2.0f / textureColumns))) / halfWindowWidth);
	vertexY = (halfWindowWidth - (halfWindowWidth - (textHeight / 2.0f / textureLines))) / halfWindowWidth;



	/* Texture coordinates handling */
	currentLine = std::max( 1, std::min(currentLineRef, textureLines));
	/*OpenGL handles vertically inverted textures, so the first line to be processed is actually the last, 
	thats why we invert the recieved value*/
	glCurrentLine = currentLine * -1.0f + textureLines+ 1.0f;
	currentColumn = std::max(1, std::min(currentColumnRef, textureColumns));

	bottomFrameVertice = (1.0f / textureLines * glCurrentLine) - (1.0f / textureLines);
	topFrameVertice = 1.0f / textureLines * glCurrentLine;
	rightFrameVertice = 1.0f / textureColumns * currentColumn;
	leftFrameVertice = (1.0f / textureColumns * currentColumn) - (1.0f / textureColumns);

	/* Finally setting the vertices */
	RefreshVertices(0, 0);
}

//TILED 
RenderObject::RenderObject(int layerRef, int idRef, Texture* textureRef, class GameEngine* engineRef, int xTileAmount, int yTileAmount)
{
	layer = layerRef;
	id = idRef;
	myTexture = textureRef;
	myEngineRef = engineRef;

	colorOverlay.x = 1.0f;
	colorOverlay.y = 1.0f;
	colorOverlay.z = 1.0f;

	tiled = true;
	xTile = xTileAmount;
	yTile = yTileAmount;

	/* Vertices handling */
	textWidth = myTexture->GetTextureDimensions().width;
	textHeight = myTexture->GetTextureDimensions().height;
	halfWindowWidth = myEngineRef->GetWindowWidth() / 2.0f;
	halfWindowHeight = myEngineRef->GetWindowHeight() / 2.0f;
	vertexX = (halfWindowWidth - (halfWindowWidth - (textWidth / 2.0f))) / halfWindowWidth;
	vertexY = (halfWindowWidth - (halfWindowWidth - (textHeight / 2.0f))) / halfWindowWidth;

	OGvertexX = vertexX;
	OGvertexY = vertexY;

	/* Texture coordinates handling */
	bottomFrameVertice = 0.0f;
	topFrameVertice = 1.0f;
	rightFrameVertice = 1.0f;
	leftFrameVertice = 0.0f;

	/* Finally setting the vertices */
	RefreshVertices(0, 0);
}

/* CONSTRUCTORS END */


void RenderObject::SetScreenRectValValue(int newW, int newH, int newX, int newY)
{
	screenRectValue.width = newW;
	screenRectValue.height = newH;
	screenRectValue.xPos = newX;
	screenRectValue.yPos = newY;
}

void RenderObject::SetTextRectValValue(int newW, int newH, int newX, int newY)
{
	textRectValue.width = newW;
	textRectValue.height = newH;
	textRectValue.xPos = newX;
	textRectValue.yPos = newY;
}

void RenderObject::RefreshVertices(int xMultiplier, int yMultiplier)
{
	float tempVertices[] = {
	vertexX + vertexX * xMultiplier * 2,  vertexY + vertexY * yMultiplier * 2,    rightFrameVertice, topFrameVertice,    // top right
	vertexX + vertexX * xMultiplier * 2,  -vertexY + vertexY * yMultiplier * 2,   rightFrameVertice, bottomFrameVertice, // bottom right
	-vertexX + vertexX * xMultiplier * 2, -vertexY + vertexY * yMultiplier * 2,   leftFrameVertice, bottomFrameVertice,  // bottom left
	-vertexX + vertexX * xMultiplier * 2, vertexY + vertexY * yMultiplier * 2,    leftFrameVertice, topFrameVertice      // top left
	};

	for (int i = 0; i < 16; ++i)
	{
		vertices[i] = tempVertices[i];
	}
}

void RenderObject::SetOffsets(float x, float y)
{
	xOffset = ((halfWindowWidth - (halfWindowWidth - x)) / halfWindowWidth);
	yOffset = ((halfWindowWidth - (halfWindowWidth - y)) / halfWindowWidth);
}

void RenderObject::SetRotation(float angleRef)
{
	rotAngle = angleRef;
}

void RenderObject::SetColorOverlay(float r, float g, float b)
{
	colorOverlay.x = r;
	colorOverlay.y = g;
	colorOverlay.z = b;
}

void RenderObject::RenderStill(ShaderProgram* shaderProgramRef)
{
	shaderProgramRef->SetVerticesToRender(vertices);
 	shaderProgramRef->SetModelMatrix(xOffset, yOffset, rotAngle);
 	shaderProgramRef->SetColorOverlayUniform(colorOverlay);
	myTexture->BindTexture();
	shaderProgramRef->SetTextureUniform(myTexture->GetTexture());
	shaderProgramRef->RenderVertices();
}

void RenderObject::RenderAnimated(ShaderProgram* shaderProgramRef, float deltaTimeRef)
{
	timestamp += deltaTimeRef;

	if (!paused && timestamp >= 1 / animationSpeed)
	{
		timestamp = 0;

		currentColumn += (reversed) ? -1 : +1; // Advance animation in intended direction

		if (!reversed && currentColumn > textureColumns) // Reset if out of bounds "Columns"
		{
			//Columns
			currentColumn = 1;

			//Rows
			currentLine += 1;

			if (currentLine > textureLines) //Reset if out of bounds "Lines"
			{
				currentLine = 1;
			}
		}
		else if (reversed && currentColumn < 1) // Reverse
		{
			//Columns
			currentColumn = textureColumns;

			//Rows
			currentLine -= 1;

			if (currentLine < 1)
			{
				currentLine = textureLines;
			}
		}



		glCurrentLine = currentLine * -1.0f + textureLines + 1.0f;

		bottomFrameVertice = (1.0f / textureLines * glCurrentLine) - (1.0f / textureLines);
		topFrameVertice = 1.0f / textureLines * glCurrentLine;
		rightFrameVertice = 1.0f / textureColumns * currentColumn;
		leftFrameVertice = (1.0f / textureColumns * currentColumn) - (1.0f / textureColumns);

		RefreshVertices(0, 0);
	}


	shaderProgramRef->SetVerticesToRender(vertices);
	shaderProgramRef->SetModelMatrix(xOffset, yOffset, rotAngle);
	shaderProgramRef->SetColorOverlayUniform(colorOverlay);
	myTexture->BindTexture();
	shaderProgramRef->SetTextureUniform(myTexture->GetTexture());
	shaderProgramRef->RenderVertices();
}

void RenderObject::RenderTiled(ShaderProgram* shaderProgramRef)
{
	myTexture->BindTexture();
	shaderProgramRef->SetTextureUniform(myTexture->GetTexture());
	shaderProgramRef->SetColorOverlayUniform(colorOverlay);
	shaderProgramRef->SetModelMatrix(xOffset, yOffset, rotAngle);

	//Y
	for (int iy = 0; iy < yTile; ++iy)
	{
		RefreshVertices(iy, 0);
		shaderProgramRef->SetVerticesToRender(vertices);
		shaderProgramRef->RenderVertices();

		//X
		for (int ix = 0; ix < xTile; ++ix)
		{
			RefreshVertices(iy, ix);
			shaderProgramRef->SetVerticesToRender(vertices);
			shaderProgramRef->RenderVertices();
		}
	}
}

void RenderObject::PauseAnimation(bool yesNo)
{
	paused = yesNo;
}

void RenderObject::ReverseAnimation(bool yesNo)
{
	reversed = yesNo;
}

void RenderObject::SkipToFrame(int line, int column)
{
	currentLine = line;
	currentColumn = column;
}

void RenderObject::ReplaceTexture(Texture* textureRef, int currentLineRef, int currentColumnRef)
{
	myTexture = textureRef;

	/* Vertices handling */
	textWidth = textureRef->GetTextureDimensions().width;
	textHeight = textureRef->GetTextureDimensions().height;
	textureLines = textureRef->GetLines();
	textureColumns = textureRef->GetColumns();

	vertexX = ((halfWindowWidth - (halfWindowWidth - (textWidth / 2.0f / textureColumns))) / halfWindowWidth);
	vertexY = (halfWindowWidth - (halfWindowWidth - (textHeight / 2.0f / textureLines))) / halfWindowWidth;


	/* Texture coordinates handling */
	currentLine = std::max(1, std::min(currentLineRef, textureLines));
	/*OpenGL handles vertically inverted textures, so the first line to be processed is actually the last, 
	thats why we invert the recieved value*/
	glCurrentLine = currentLine * -1.0f + textureLines + 1.0f;
	currentColumn = std::max(1, std::min(currentColumnRef, textureColumns));

	bottomFrameVertice = (1.0f / textureLines * glCurrentLine) - (1.0f / textureLines);
	topFrameVertice = 1.0f / textureLines * glCurrentLine;
	rightFrameVertice = 1.0f / textureColumns * currentColumn;
	leftFrameVertice = (1.0f / textureColumns * currentColumn) - (1.0f / textureColumns);

	/* Finally setting the vertices */
	RefreshVertices(0, 0);
}

int RenderObject::GetCurrentFrame()
{
	return (float)textRectValue.xPos / frameWidth + (((float)textRectValue.yPos / frameHeight) * ((float)textureWidth / frameWidth));
}

RenderObject::~RenderObject() 
{
	myTexture = nullptr;
	myEngineRef = nullptr;	
}

