#pragma once
#include"Shader.h"
#include"Camera.h"
#include"Mats.h"
#include"Light.h"
#include<string>
#include<vector>

class WaterShader : public Shader
{
public:
	static const int MAX_LIGHTS = 4;
	char* vertaxShaderLocation = "waterVertex.glsl";
	char* fragmentshaderLocation = "waterFragment.glsl";
	int locationTransformation;
	int locationProjection;
	int locationView;
	int location_reflactionTexture;
	int location_refractionTexture;
	int location_DuDv;
	int location_waterMoveOffSet;
	int location_NormalMap;
	int location_cameraLocation;
	int locationlightPosition[MAX_LIGHTS];
	int locationlightColour[MAX_LIGHTS];
	int locationAttenuation[MAX_LIGHTS];

	virtual void getAllUniformLocations() override;
	WaterShader::WaterShader();

	void loadTransformation(glm::fmat4 matrix) {
		Shader::loadMatrixUni(matrix, locationTransformation);
	}

	void loadCameralocation(glm::fvec3 cameraLocation) {
		Shader::loadvectorUni(cameraLocation, location_cameraLocation);
	}

	void loadProjection(glm::fmat4 matrix) {
		Shader::loadMatrixUni(matrix, locationProjection);
	}

	void loadView(Camera& camera) {
		glm::fmat4 ViewMatrix = Mats::createView(camera);
		Shader::loadMatrixUni(ViewMatrix, locationView);
		Shader::loadvectorUni(camera.CameraLocation, location_cameraLocation);
	}

	void LoadWaterMoveOffSet(float offset) { 

		Shader::loadFloatUni(offset, location_waterMoveOffSet);
	};
	void loadLight(std::vector<Light>& lights);

	void connectTectureUnit() {

		Shader::loadIntUni(0, location_reflactionTexture);
		Shader::loadIntUni(1, location_refractionTexture);
		Shader::loadIntUni(2, location_DuDv);
		Shader::loadIntUni(3, location_NormalMap);


	};
};

