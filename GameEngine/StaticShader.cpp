#include "StaticShader.h"



void StaticShader::getAllUniformLocations()
{
	locationTransformation = Shader::GetUniformlocation("transform");
	locationProjection = Shader::GetUniformlocation("projection");
	locationView = Shader::GetUniformlocation("view");
}

StaticShader::StaticShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}


StaticShader::~StaticShader()
{
}
