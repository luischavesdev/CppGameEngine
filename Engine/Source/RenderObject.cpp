#include "RenderObject.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Engine.h"

RenderObject::RenderObject(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef) //STILL
{
	InitSetup(layerRef, idRef, textureRef,engineRef);
	TextureSetup(textureRef);
}

RenderObject::RenderObject(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef, float playbackSpeedRef, int currentLineRef, 
	int currentColumnRef) //ANIMATED
{
	animated = true;
	animationSpeed = playbackSpeedRef;

	InitSetup(layerRef, idRef, textureRef, engineRef);
	TextureSetup(textureRef, true, currentLineRef, currentColumnRef);
}

RenderObject::RenderObject(int layerRef, int idRef, Texture* textureRef, class GameEngine* engineRef, int xTileAmount, 
	int yTileAmount) //TILED
{
	tiled = true;
	tileMltplr.x = xTileAmount;
	tileMltplr.y = yTileAmount;

	InitSetup(layerRef, idRef, textureRef, engineRef);
	TextureSetup(textureRef);
}

// --- || Render Funcs || ---

void RenderObject::RenderStill(ShaderProgram* shaderProgramRef)
{
	SendToShader(shaderProgramRef, true);
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

		RefreshFrameVertices();
		RefreshVertices(0, 0);
	}

	SendToShader(shaderProgramRef, true);
}

void RenderObject::RenderTiled(ShaderProgram* shaderProgramRef)
{
	SendToShader(shaderProgramRef, false);

	//Y
	for (int iy = 0; iy < tileMltplr.y; ++iy)
	{
		RefreshVertices(iy, 0);
		shaderProgramRef->SetVerticesToRender(vertices);
		shaderProgramRef->RenderVertices();

		//X
		for (int ix = 0; ix < tileMltplr.x; ++ix)
		{
			RefreshVertices(iy, ix);
			shaderProgramRef->SetVerticesToRender(vertices);
			shaderProgramRef->RenderVertices();
		}
	}
}

// --- || Setters || ---

void RenderObject::ReplaceTexture(Texture* textureRef, bool animatedRef, int currentLineRef, int currentColumnRef)
{
	TextureSetup(textureRef, animatedRef, currentLineRef, currentColumnRef);
}

void RenderObject::SetOffsets(float x, float y)
{
	transformOffset.x = ((halfWindowWidth - (halfWindowWidth - x)) / halfWindowWidth);
	transformOffset.y = ((halfWindowWidth - (halfWindowWidth - y)) / halfWindowWidth);
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

// --- || Internal Setup || ---

void RenderObject::InitSetup(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef)
{
	layer = layerRef;
	id = idRef;
	myEngineRef = engineRef;

	colorOverlay.x = 1.0f;
	colorOverlay.y = 1.0f;
	colorOverlay.z = 1.0f;

	halfWindowWidth = myEngineRef->GetWindowWidth() / 2.0f;
	halfWindowHeight = myEngineRef->GetWindowHeight() / 2.0f;
}

void RenderObject::TextureSetup(Texture* textureRef, bool animatedRef, int currentLineRef, int currentColumnRef)
{
	myTexture = textureRef;
	textWidth = textureRef->GetTextureDimensions().width;
	textHeight = textureRef->GetTextureDimensions().height;

	if (animated)
	{
		textureLines = textureRef->GetLines();
		textureColumns = textureRef->GetColumns();

		currentLine = std::max(1, std::min(currentLineRef, textureLines));
		//OpenGL handles vertically inverted textures, so the first line to be processed is actually the last, 
		//thats why we invert the recieved value
		glCurrentLine = currentLine * -1.0f + textureLines + 1.0f;
		currentColumn = std::max(1, std::min(currentColumnRef, textureColumns));
	}

	//Setup vertices
	vertexX = (textWidth / 2.0f / textureColumns) / halfWindowWidth;
	vertexY = (textHeight / 2.0f / textureLines) / halfWindowWidth;
	
	RefreshFrameVertices();
	RefreshVertices(0, 0);
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

void RenderObject::RefreshFrameVertices()
{
	//Setup texture mapping
	bottomFrameVertice = (1.0f / textureLines * glCurrentLine) - (1.0f / textureLines);
	topFrameVertice = 1.0f / textureLines * glCurrentLine;
	rightFrameVertice = 1.0f / textureColumns * currentColumn;
	leftFrameVertice = (1.0f / textureColumns * currentColumn) - (1.0f / textureColumns);
}

void RenderObject::SendToShader(ShaderProgram* shaderProgramRef, bool includeVertices)
{
	myTexture->BindTexture();
	shaderProgramRef->SetTextureUniform(myTexture->GetTexture());
	shaderProgramRef->SetColorOverlayUniform(colorOverlay);
	shaderProgramRef->SetModelMatrix(transformOffset.x, transformOffset.y, rotAngle);

	if (includeVertices)
	{
		shaderProgramRef->SetVerticesToRender(vertices);
		shaderProgramRef->RenderVertices();
	}
}

RenderObject::~RenderObject() 
{
	myTexture = nullptr;
	myEngineRef = nullptr;	
}