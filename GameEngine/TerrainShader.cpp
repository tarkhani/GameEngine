#include "TerrainShader.h"



void TerrainShader::getAllUniformLocations()
{
	locationTransformation = Shader::GetUniformlocation("transform");
	locationProjection = Shader::GetUniformlocation("projection");
	locationView = Shader::GetUniformlocation("view");
	locationlightPosition = Shader::GetUniformlocation("lightPosition");
	locationlightColour = Shader::GetUniformlocation("lightColour");
	locationShinedamper = Shader::GetUniformlocation("ShineDamper");
	locationReflectionScale = Shader::GetUniformlocation("ReflectionScale");
	locationskyColor = Shader::GetUniformlocation("skyColor");
	locationBackGroundTextureID = Shader::GetUniformlocation("BackGroundTexture");
	locationRTextureID = Shader::GetUniformlocation("rTexture");
	locationBTextureID = Shader::GetUniformlocation("bTexture");
	locationGTextureID = Shader::GetUniformlocation("gTexture");
	locationblendMapID = Shader::GetUniformlocation("BlendMap");
}

TerrainShader::TerrainShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
	connectTectureUnit();
}


TerrainShader::~TerrainShader()
{
}
