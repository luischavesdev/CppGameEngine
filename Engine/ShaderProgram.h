#pragma once
#include "Vector2.h"
//#include <GL\freeglut.h>

class ShaderProgram 
{
private:
	class GameEngine* myEngineRef;
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

	void SetVertexShaderSource(const char* source);

	void SetFragmentShaderSource(const char* source);

	void SetModelMatrix(float x, float y, float angle);

	void SetViewMatrix(float x, float y, float z);

	void SetPerspectiveMatrix(float fovRef);

	void SetTextureUniform(unsigned int textureRef);

	void SetColorOverlayUniform(Vector3 color);

	unsigned int GetShaderProgram();

	~ShaderProgram();
};