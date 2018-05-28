#pragma once
#include<vector>
#include "Shader.h"
#include"Camera.h"
#include"Mats.h"
#include"Light.h"
class StaticShader :
	public Shader
{

public:

	static const int MAX_LIGHTS = 4;

	char* vertaxShaderLocation = "vertaxshadercode.glsl";
	char* fragmentshaderLocation = "fragmentshader.glsl";
	int locationTransformation;
	int locationProjection;
	int locationView;
	int locationlightPosition[MAX_LIGHTS];
	int locationlightColour[MAX_LIGHTS];
	int locationAttenuation[MAX_LIGHTS];
	int locationShinedamper;
	int locationReflectionScale;
	int locationFakeLightning;
	int locationskyColor;
	int locationXYoffset;
	int locationNumberOfRows;
	int locationCulling_plane;

	virtual void getAllUniformLocations() override;
	void loadTransformation(glm::fmat4 &matrix) {
		Shader::loadMatrixUni(matrix, locationTransformation);
	}

	void loadProjection(const glm::fmat4 &matrix) {
		Shader::loadMatrixUni(matrix, locationProjection);
	}

	void loadLight(std::vector<Light>& lights) {
		for (int i = 0; i < MAX_LIGHTS; i++)
		{
			if (i<lights.size())
			{
				Shader::loadvectorUni(lights[i].position, locationlightPosition[i]);
				Shader::loadvectorUni(lights[i].colour, locationlightColour[i]);
				Shader::loadvectorUni(lights[i].attenuation, locationAttenuation[i]);

			}
			else {

				Shader::loadvectorUni(glm::fvec3(0.0f,0.0f,0.0f), locationlightPosition[i]);
				Shader::loadvectorUni(glm::fvec3(0.0f, 0.0f, 0.0f), locationlightColour[i]);
				Shader::loadvectorUni(glm::fvec3(1.0f, 0.0f, 0.0f), locationAttenuation[i]);
			}
		}
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
	void loadSkyColor(glm::vec3 &SkyColor) { Shader::loadvectorUni(SkyColor, locationskyColor); };
	void loadxyOffset(glm::vec2 &xyoffset) { Shader::loadvectorUni(xyoffset, locationXYoffset); };//load offset
	void loadNumberOfRows(float NumberOfRows) { Shader::loadFloatUni(NumberOfRows, locationNumberOfRows); };
	void loadCullingPlane(glm::fvec4 &plane) { Shader::loadvectorUni(plane, locationCulling_plane); };
	StaticShader();
	~StaticShader();
};

