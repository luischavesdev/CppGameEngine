#include <iostream>
#include <iomanip>
#include "ShaderProgram.h"
#include "GameEngine.h"
#include "glad.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#include "stb_image.h"

ShaderProgram::ShaderProgram(GameEngine* engineRef)
{
	if (engineRef != nullptr)
	{
		myEngineRef = engineRef;
	}

	windowWidth = myEngineRef->GetWindowWidth();
	windowHeight = myEngineRef->GetWindowHeight();

	//VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	//VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	float tempVertices[] = {
	0.0f, 0.0f,      1.0f, 1.0f,      // top right
	0.5f, -0.0f,     1.0f, 0.0f,      // bottom right
	-0.0f, -0.0f,    0.0f, 0.0f,      // bottom left
	-0.0f, 0.0f,     0.0f, 1.0f      // top left
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(tempVertices), tempVertices, GL_DYNAMIC_DRAW);


	//EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indiceArray), indiceArray, GL_DYNAMIC_DRAW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ShaderProgram::Start(bool defaultStart, float windowAspect)
{
	if (defaultStart)
	{
	 	//Vertex Source
	 	vertexShaderSource = R"glsl(
	 	#version 330 core
	 
		in vec2 aPos;
		in vec2 aTexCoord;
		
 		uniform mat4 model;
 		uniform mat4 view;
 		uniform mat4 projection;

		out vec2 TexCoord;

		void main()
		{
			gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
			TexCoord = aTexCoord;
		}
	 	)glsl";
	 
	 	//Fragment Source
	 	fragmentShaderSource = R"glsl(
	 	#version 330 core
	 
		in vec2 TexCoord;

		uniform sampler2D ourTexture;
		uniform vec4 ourOverlayColor;

		out vec4 FragColor;

		void main()
		{
			vec4 colTex = texture(ourTexture, TexCoord);

			if (colTex.x >= 0.9f && colTex.y <= 0.1f && colTex.z >= 0.9f)
			{
				colTex.w = 0.0f;
			}

			FragColor = colTex * ourOverlayColor;

		}
	 	)glsl";
	}


	/* SHADER CREATION AND VERIFICATION*/
	GLint success;
	char infoLog[512];

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	/* SHADER PROGRAM  */
	shaderProgram = glCreateProgram(); // Created an empty program 
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader); // Attach the shaders to the empty program
	glLinkProgram(shaderProgram); // Link the program and generate the shader program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader); // Since they were already linked to the program; we dont need their reference anymore
	glDeleteShader(fragmentShader);


	/* UNIFORMS AND ATTRIBUTES  */
	posAttrib = glGetAttribLocation(shaderProgram, "aPos");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	texAttrib = glGetAttribLocation(shaderProgram, "aTexCoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	textureUniform = glGetUniformLocation(shaderProgram, "ourTexture");

	colorOverlayUniform = glGetUniformLocation(shaderProgram, "ourOverlayColor");
	glUniform4f(colorOverlayUniform, 1.0f, 1.0f, 1.0f, 1.0f);




	//Matrices:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	modelMatUni = glGetUniformLocation(shaderProgram, "model");

 	viewMatUni = glGetUniformLocation(shaderProgram, "view");
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -1.8f));
	glUniformMatrix4fv(viewMatUni, 1, GL_FALSE, glm::value_ptr(viewMat));

 	perspectiveMatUni = glGetUniformLocation(shaderProgram, "projection");
	glm::mat4 projectionMat;
	projectionMat = glm::perspective(glm::radians(45.0f), windowWidth/ windowHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(perspectiveMatUni, 1, GL_FALSE, glm::value_ptr(projectionMat));


}

void ShaderProgram::RenderVertices()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void ShaderProgram::SetVerticesToRender(float verticesRef[16])
{
	float tempVertices[] = {
	0.0f, 0.0f,      1.0f, 1.0f,      // top right
	0.0f, -0.0f,     1.0f, 0.0f,      // bottom right
	-0.0f, -0.0f,    0.0f, 0.0f,      // bottom left
	-0.0f, 0.0f,     0.0f, 1.0f      // top left
	};

	//Copying recieved array into local one
	for (int i = 0; i < 16; ++i)
	{
		tempVertices[i] = verticesRef[i];
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tempVertices), &tempVertices);
}

void ShaderProgram::SetVertexShaderSource(const char* source)
{
	vertexShaderSource = source;
}

void ShaderProgram::SetFragmentShaderSource(const char* source)
{
	fragmentShaderSource = source;
}

void ShaderProgram::SetModelMatrix(float x, float y, float angle)
{
	glm::mat4 tempMatTrans = glm::mat4(1.0f);
	tempMatTrans = glm::translate(tempMatTrans, glm::vec3(x, y, 0.0f));

	glm::mat4 tempMat(1.0f);
	tempMat = glm::rotate(tempMat, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));




	tempMat = tempMatTrans * tempMat;

	glUniformMatrix4fv(modelMatUni, 1, GL_FALSE, glm::value_ptr(tempMat));

}

void ShaderProgram::SetViewMatrix(float x, float y, float z)
{
	glm::mat4 tempMat = glm::mat4(1.0f);
	tempMat = glm::translate(tempMat, glm::vec3(x, y, 0.0f));

	glUniformMatrix4fv(viewMatUni, 1, GL_FALSE, glm::value_ptr(tempMat));
}

void ShaderProgram::SetPerspectiveMatrix(float fovRef)
{
	glm::mat4 tempMat;
	tempMat = glm::perspective(glm::radians(fovRef), windowWidth / windowHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(perspectiveMatUni, 1, GL_FALSE, glm::value_ptr(tempMat));
}

void ShaderProgram::SetTextureUniform(unsigned int textureRef)
{
	glUniform1i(textureUniform, textureRef);
}

void ShaderProgram::SetColorOverlayUniform(Vector3 color)
{
	glUniform4f(colorOverlayUniform, color.x, color.y, color.z, 1.0f);
}

unsigned int ShaderProgram::GetShaderProgram()
{
	return shaderProgram;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteShader(shaderProgram);

	vertexShaderSource = nullptr;
	fragmentShaderSource = nullptr;
}
