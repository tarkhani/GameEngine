#include "StaticShader.h"
#include<string>



void StaticShader::getAllUniformLocations()
{
	locationTransformation = Shader::GetUniformlocation("transform");
	locationProjection = Shader::GetUniformlocation("projection");
	locationView = Shader::GetUniformlocation("view");
	locationShinedamper = Shader::GetUniformlocation("ShineDamper");
	locationReflectionScale = Shader::GetUniformlocation("ReflectionScale");
	locationFakeLightning = Shader::GetUniformlocation("FakeLightning");
	locationskyColor = Shader::GetUniformlocation("skyColor");
	locationNumberOfRows = Shader::GetUniformlocation("numberOfRows");
	locationXYoffset = Shader::GetUniformlocation("xyoffset");
	locationCulling_plane = Shader::GetUniformlocation("plane");
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		std::string tempString = ("lightPosition[" + std::to_string(i) + "]");
	    char *locationInArray = const_cast<char *>(tempString.c_str());
		locationlightPosition[i] = Shader::GetUniformlocation(locationInArray);

		tempString= ("lightColour[" + std::to_string(i) + "]");
		locationInArray = const_cast<char *>(tempString.c_str());
		locationlightColour[i]= Shader::GetUniformlocation(locationInArray);

		tempString = ("attenuation[" + std::to_string(i) + "]");
		locationInArray = const_cast<char *>(tempString.c_str());
		locationAttenuation[i] = Shader::GetUniformlocation(locationInArray);
		
	}
	
}

StaticShader::StaticShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}


StaticShader::~StaticShader()
{
	
}
