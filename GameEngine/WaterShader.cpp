#include "WaterShader.h"



void WaterShader::getAllUniformLocations()
{
	locationTransformation = Shader::GetUniformlocation("modelMatrix");
	locationProjection = Shader::GetUniformlocation("projectionMatrix");
	locationView = Shader::GetUniformlocation("viewMatrix");
	location_reflactionTexture = Shader::GetUniformlocation("reflactionTexture");
	location_refractionTexture = Shader::GetUniformlocation("refractionTexture");
	location_DuDv= Shader::GetUniformlocation("DuDv");
	location_waterMoveOffSet = Shader::GetUniformlocation("waterMoveOffSet");
	location_NormalMap= Shader::GetUniformlocation("NormalMap");
	location_cameraLocation= Shader::GetUniformlocation("cameraLocation");
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

WaterShader::WaterShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}

void WaterShader::loadLight(std::vector<Light>& lights)
{
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		if (i<lights.size())
		{
			Shader::loadvectorUni(lights[i].position, locationlightPosition[i]);
			Shader::loadvectorUni(lights[i].colour, locationlightColour[i]);
			Shader::loadvectorUni(lights[i].attenuation, locationAttenuation[i]);

		}
		else {

			Shader::loadvectorUni(glm::fvec3(0.0f, 0.0f, 0.0f), locationlightPosition[i]);
			Shader::loadvectorUni(glm::fvec3(0.0f, 0.0f, 0.0f), locationlightColour[i]);
			Shader::loadvectorUni(glm::fvec3(1.0f, 0.0f, 0.0f), locationAttenuation[i]);
		}
	}
}



