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
	location_Normal= Shader::GetUniformlocation("Normal");
	location_cameraLocation= Shader::GetUniformlocation("cameraLocation");
}

WaterShader::WaterShader()
{
	Shader::shaderProgeram(vertaxShaderLocation, fragmentshaderLocation);
	getAllUniformLocations();
}



