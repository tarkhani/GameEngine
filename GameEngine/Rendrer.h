#pragma once
#include"RawModel.h"
#include"textureModel.h"
#include"RawModel.h"
#include"entity.h"
#include"StaticShader.h"

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
public:
	
	void prepare();
	void render(entity entityToRender,StaticShader shader);

	Rendrer(StaticShader Shader);
	~Rendrer();
};

