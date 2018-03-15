#pragma once
#include"RawModel.h"
#include"textureModel.h"
#include"StaticShader.h"
#include"GL\glew.h"
#include<iostream>
#include"Mats.h"
#include<map>
#include<list>
#include"entity.h"

static void _CheckGLError(const char* file, int line)
{
	GLenum err(glGetError());

	while (err != GL_NO_ERROR)
	{
		std::string error;
		switch (err)
		{
		case GL_INVALID_OPERATION:  error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:       error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:      error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:      error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}
		std::cout << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
		err = glGetError();
	}

	return;
}
#define CheckGLError() _CheckGLError(__FILE__, __LINE__);


class Rendrer
{
private:

	StaticShader shader;

public:
	

	void prepareTextureModel(textureModel textureModel);
	void unboundTextureModel();
	void prepareInstance(entity entity);
	void render(std::map<textureModel, std::list<entity>> entities);

	Rendrer(StaticShader& Shader, const  glm::mat4 &proj);
	~Rendrer();
};

