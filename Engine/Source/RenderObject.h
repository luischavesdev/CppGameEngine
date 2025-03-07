#pragma once
#include "VectorCustom.h"

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
	float vertices[16];

	float textWidth = 0;
	float textHeight = 0;

	//Animation related vars
	float timestamp = 0.0f;
	float animationSpeed = 0;
	int textureLines = 1;
	int textureColumns = 1;
	int currentLine = 1;
	int glCurrentLine = 1;
	int currentColumn = 1;

	float bottomFrameVertice = 0;
	float topFrameVertice = 0;
	float rightFrameVertice = 0;
	float leftFrameVertice = 0;

	bool animated = false;
	bool reversed = false;
	bool paused = false;

	//Tilling related vars
	bool tiled = false;
	Vector2 tileMltplr;

	//Transformation related vars
	Vector2 transformOffset;
	float rotAngle = 0.0f;

	Vector3 colorOverlay;
	

	RenderObject(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef);
	RenderObject(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef, float playbackSpeedRef, int currentLineRef,
		int currentColumnRef);
	RenderObject(int layerRef, int idRef, Texture* textureRef, class GameEngine* engineRef, int xTileAmount, int yTileAmount);

	void RenderStill(class ShaderProgram* shaderProgramRef);
	void RenderAnimated(ShaderProgram* shaderProgramRef, float deltaTimeRef);
	void RenderTiled(ShaderProgram* shaderProgramRef);
	
	void ReplaceTexture(Texture* textureRef, bool animatedRef = false, int currentLineRef = 1, int currentColumnRef = 1);
	void SetOffsets(float x, float y);
	void SetRotation(float angleRef);
	void SetColorOverlay(float r, float g, float b);
	void PauseAnimation(bool yesNo);
	void ReverseAnimation(bool yesNo);
	void SkipToFrame(int line, int column);

	~RenderObject();


private:
	void InitSetup(int layerRef, int idRef, Texture* textureRef, GameEngine* engineRef);
	void TextureSetup(Texture* textureRef, bool animatedRef = false, int currentLineRef = 1, int currentColumnRef = 1);

	void RefreshVertices(int xMultiplier, int yMultiplier);
	void RefreshFrameVertices();

	void SendToShader(ShaderProgram* shaderProgramRef, bool includeVertices);
};
