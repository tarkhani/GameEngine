#pragma once
#include "Shader.h"
#include"Camera.h"
#include"Mats.h"
#include"Light.h"
class StaticShader :
	public Shader
{

public:

	char* vertaxShaderLocation = "vertaxshadercode.glsl";
	char* fragmentshaderLocation = "fragmentshader.glsl";
	int locationTransformation;
	int locationProjection;
	int locationView;
	int locationlightPosition;
	int locationlightColour;
	int locationShinedamper;
	int locationReflectionScale;
	int locationFakeLightning;
	int locationskyColor;

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
		glm::fmat4 ViewMatrix =Mats::createView(camera);
		Shader::loadMatrixUni(ViewMatrix, locationView);
	}
	void loadReflactionAttrib(float  ShineDamper, float ReflectionScale) {
		Shader::loadFloatUni(ShineDamper, locationShinedamper);
		Shader::loadFloatUni(ReflectionScale, locationReflectionScale);
	}
	void loadFakeLightning(bool FakeLightning) { Shader::loadBoolUni(FakeLightning,locationFakeLightning); };
	void loadSkyColor(glm::vec3 SkyColor) { Shader::loadvectorUni(SkyColor, locationskyColor); };
	StaticShader();
	~StaticShader();
};

