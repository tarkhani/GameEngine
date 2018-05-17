#include "WaterShader.h"



void WaterShader::getAllUniformLocations()
{
	locationTransformation = Shader::GetUniformlocation("modelMatrix");
	locationProjection = Shader::GetUniformlocation("projectionMatrix");
	locationView = Shader::GetUniformlocation("viewMatrix");
}

WaterShader::WaterShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}



