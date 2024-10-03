#pragma once
#include "RectValues.h"
#include "Vector2.h"

class RenderObject 
{
public:
	int layer;
	int id;
	class Texture* myTexture = nullptr;
	class GameEngine* myEngineRef = nullptr;
	float halfWindowWidth;
	float halfWindowHeight;

	float vertexX;
	float vertexY;
	float OGvertexX;
	float OGvertexY;
	float vertices[16];

	float textWidth = NULL;
	float textHeight = NULL;

	//Animation related vars
	float timestamp = 0.0f;
	float animationSpeed = NULL;
	int textureLines = NULL;
	int textureColumns = NULL;
	int currentLine = NULL;
	int glCurrentLine = NULL;
	int currentColumn = NULL;

	float bottomFrameVertice = NULL;
	float topFrameVertice = NULL;
	float rightFrameVertice = NULL;
	float leftFrameVertice = NULL;

	bool animated = false;
	bool reversed = false;
	bool paused = false;

	//Tilling related vars
	bool tiled = false;
	int xTile = NULL;
	int yTile = NULL;

	//Transformation related vars
	float xOffset = 0.0f;
	float yOffset = 0.0f;
	float rotAngle = 0.0f;
	Vector3 colorOverlay;
	
	//Legacy
	RectValues textRectValue;
	RectValues screenRectValue;
	class SDL_Rect* sdlTextRect;
	SDL_Rect* sdlScreenRect;
	int frameWidth = NULL;
	int frameHeight = NULL;
	float textureHeight = NULL;
	float textureWidth = NULL;


	
	



	//Still
	RenderObject(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef);

	//Animated
	RenderObject(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef, float playbackSpeedRef, int currentLineRef,
		int currentColumnRef);

	//Tiled 
	RenderObject(int layerRef, int idRef, Texture* textureRef, class GameEngine* engineRef, int xTileAmount, int yTileAmount);

	void SetScreenRectValValue(int newW, int newH,  int newX, int newY);

	void SetTextRectValValue(int newW, int newH,  int newX, int newY);

	void RefreshVertices(int xMultiplier, int yMultiplier);

	void SetOffsets(float x, float y);

	void SetRotation(float angleRef);

	void SetColorOverlay(float r, float g, float b);

	void RenderStill(class ShaderProgram* shaderProgramRef);

	void RenderAnimated(ShaderProgram* shaderProgramRef, float deltaTimeRef);

	void RenderTiled(ShaderProgram* shaderProgramRef);

	void PauseAnimation(bool yesNo);

	void ReverseAnimation(bool yesNo);

	void SkipToFrame(int line, int column);

	void ReplaceTexture(Texture* textureRef, int currentLineRef, int currentColumnRef);

	int GetCurrentFrame();

	~RenderObject();
};