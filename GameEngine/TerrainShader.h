#pragma once
#include"Shader.h"
#include"Camera.h"
#include"Mats.h"
#include"Light.h"
class TerrainShader : public Shader
{
public:

	char* vertaxShaderLocation = "Terrain_vertaxshadercode.glsl";
	char* fragmentshaderLocation = "Terrain_fragmentshader.glsl";
	int locationTransformation;
	int locationProjection;
	int locationView;
	int locationlightPosition;
	int locationlightColour;
	int locationShinedamper;
	int locationReflectionScale;
	int locationskyColor;
	int locationBackGroundTextureID;
	int locationRTextureID;
	int locationBTextureID;
	int locationGTextureID;
	int locationblendMapID;

	virtual void getAllUniformLocations() override;
	void loadTransformation(glm::fmat4 matrix) {
		Shader::loadMatrixUni(matrix, locationTransformation);
	}

	void loadProjection(glm::fmat4 matrix) {
		Shader::loadMatrixUni(matrix, locationProjection);
	}

	void loadLight(Light& light) {
		Shader::loadvectorUni(light.position, locationlightPosition);
		Shader::loadvectorUni(light.colour, locationlightColour);
	}

	void loadView(Camera& camera) {
		glm::fmat4 ViewMatrix = Mats::createView(camera);
		Shader::loadMatrixUni(ViewMatrix, locationView);
	}
	void loadReflactionAttrib(float  ShineDamper, float ReflectionScale) {
		Shader::loadFloatUni(ShineDamper, locationShinedamper);
		Shader::loadFloatUni(ReflectionScale, locationReflectionScale);
	}
	void loadSkyColor(glm::vec3 SkyColor) { Shader::loadvectorUni(SkyColor, locationskyColor); };
	void connectTectureUnit() {
	
		Shader::loadIntUni(0,locationBackGroundTextureID);
		Shader::loadIntUni(1,locationRTextureID);
		Shader::loadIntUni(2,locationGTextureID);
		Shader::loadIntUni(3,locationBTextureID);
		Shader::loadIntUni(4,locationblendMapID);
	
	
	};
	TerrainShader();
	~TerrainShader();
};

