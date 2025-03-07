#pragma once
#include "VectorCustom.h"

class ShaderProgram 
{
private:
	class GameEngine* myEngineRef = nullptr;
	float windowWidth;
	float windowHeight;
	unsigned int shaderProgram;
	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	unsigned int indiceArray[6] = {
	0, 1, 2, // first triangle
	0, 2, 3 // second triangle
	};

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	unsigned int posAttrib;
	unsigned int texAttrib;
	unsigned int viewMatUni;
	unsigned int modelMatUni;
	unsigned int perspectiveMatUni;
	unsigned int textureUniform;
	unsigned int colorOverlayUniform;


public:
	ShaderProgram(GameEngine* engineRef);

	void Start(bool defaultStart, float windowAspect);

	void RenderVertices();

	void SetVerticesToRender(float verticesRef[16]);
	void SetModelMatrix(float x, float y, float angle);
	void SetTextureUniform(unsigned int textureRef);
	void SetColorOverlayUniform(Vector3 color);

	// Setters in case default start is not used
	void SetVertexShaderSource(const char* source);
	void SetFragmentShaderSource(const char* source);

	~ShaderProgram();
};
