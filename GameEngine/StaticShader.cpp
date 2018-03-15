#include "StaticShader.h"



void StaticShader::getAllUniformLocations()
{
	locationTransformation = Shader::GetUniformlocation("transform");
	locationProjection = Shader::GetUniformlocation("projection");
	locationView = Shader::GetUniformlocation("view");
	locationlightPosition = Shader::GetUniformlocation("lightPosition");
	locationlightColour = Shader::GetUniformlocation("lightColour");
	locationShinedamper = Shader::GetUniformlocation("ShineDamper");
	locationReflectionScale = Shader::GetUniformlocation("ReflectionScale");
}

StaticShader::StaticShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}


StaticShader::~StaticShader()
{
}
