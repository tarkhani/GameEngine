#include "TerrainShader.h"
#include<string>



void TerrainShader::getAllUniformLocations()
{
	locationTransformation = Shader::GetUniformlocation("transform");
	locationProjection = Shader::GetUniformlocation("projection");
	locationView = Shader::GetUniformlocation("view");
	locationShinedamper = Shader::GetUniformlocation("ShineDamper");
	locationReflectionScale = Shader::GetUniformlocation("ReflectionScale");
	locationskyColor = Shader::GetUniformlocation("skyColor");
	locationBackGroundTextureID = Shader::GetUniformlocation("BackGroundTexture");
	locationRTextureID = Shader::GetUniformlocation("rTexture");
	locationBTextureID = Shader::GetUniformlocation("bTexture");
	locationGTextureID = Shader::GetUniformlocation("gTexture");
	locationblendMapID = Shader::GetUniformlocation("BlendMap");

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		std::string tempString = ("lightPosition[" + std::to_string(i) + "]");
		char *locationInArray = const_cast<char *>(tempString.c_str());
		locationlightPosition[i] = Shader::GetUniformlocation(locationInArray);

		tempString = ("lightColour[" + std::to_string(i) + "]");
		locationInArray = const_cast<char *>(tempString.c_str());
		locationlightColour[i] = Shader::GetUniformlocation(locationInArray);

		tempString = ("attenuation[" + std::to_string(i) + "]");
		locationInArray = const_cast<char *>(tempString.c_str());
		locationAttenuation[i] = Shader::GetUniformlocation(locationInArray);

	}
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
