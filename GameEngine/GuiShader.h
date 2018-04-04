#pragma once
#include "Shader.h"
class GuiShader :
	public Shader
{
public:

	char* vertaxShaderLocation = "guiVertexShader.txt";
	char* fragmentshaderLocation = "guiFragmentShader.txt";
	int locationTransformationMatrix;

	void getAllUniformLocations()override;
	void loadTransformation(glm::mat4 matrix);
	GuiShader();
	~GuiShader();
};

