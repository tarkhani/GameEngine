#include "WaterShader.h"



void WaterShader::getAllUniformLocations()
{
	locationTransformation = Shader::GetUniformlocation("modelMatrix");
	locationProjection = Shader::GetUniformlocation("projectionMatrix");
	locationView = Shader::GetUniformlocation("viewMatrix");
	location_reflactionTexture = Shader::GetUniformlocation("reflactionTexture");
	location_refractionTexture = Shader::GetUniformlocation("refractionTexture");
}

WaterShader::WaterShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}



