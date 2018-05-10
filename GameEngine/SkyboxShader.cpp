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
	location_fogColour = Shader::GetUniformlocation("fogColour");
	location_blendFactor = Shader::GetUniformlocation("blendFactor");
	location_CubeMap1 = Shader::GetUniformlocation("cubeMap");
	location_CubeMap2 = Shader::GetUniformlocation("cubeMap2");
}


SkyboxShader::~SkyboxShader()
{
}
