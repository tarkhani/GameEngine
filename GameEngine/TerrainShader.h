#pragma once
#include<vector>
#include"Shader.h"
#include"Camera.h"
#include"Mats.h"
#include"Light.h"

class TerrainShader : public Shader
{
public:

	static const int MAX_LIGHTS = 4;

	char* vertaxShaderLocation = "Terrain_vertaxshadercode.glsl";
	char* fragmentshaderLocation = "Terrain_fragmentshader.glsl";
	int locationTransformation;
	int locationProjection;
	int locationView;
	int locationlightPosition[MAX_LIGHTS];
	int locationlightColour[MAX_LIGHTS];
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

	void loadLight(std::vector<Light>& lights) {
		for (int i = 0; i < MAX_LIGHTS; i++)
		{
			if (i<lights.size())
			{
				Shader::loadvectorUni(lights[i].position, locationlightPosition[i]);
				Shader::loadvectorUni(lights[i].colour, locationlightColour[i]);
				
			}
			else {

				Shader::loadvectorUni(glm::fvec3(0.0f, 0.0f, 0.0f), locationlightPosition[i]);
				Shader::loadvectorUni(glm::fvec3(0.0f, 0.0f, 0.0f), locationlightColour[i]);
				
				
			}
		}
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

