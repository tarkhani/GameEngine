#include "GuiShader.h"



void GuiShader::getAllUniformLocations()
{
	locationTransformationMatrix = Shader::GetUniformlocation("transformationMatrix");
}

void GuiShader::loadTransformation(glm::mat4 matrix)
{
	Shader::loadMatrixUni(matrix, locationTransformationMatrix);
}

GuiShader::GuiShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}


GuiShader::~GuiShader()
{
}
