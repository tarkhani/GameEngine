#include "SkyboxShader.h"



SkyboxShader::SkyboxShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}

void SkyboxShader::getAllUniformLocations()
{
	location_projectionMatrix = Shader::GetUniformlocation("projectionMatrix");
	location_viewMatrix = Shader::GetUniformlocation("viewMatrix");
}


SkyboxShader::~SkyboxShader()
{
}
