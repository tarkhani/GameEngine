#pragma once
#include"Shader.h"
#include"Camera.h"
#include"Mats.h"

class WaterShader : public Shader
{
public:
	char* vertaxShaderLocation = "waterVertex.glsl";
	char* fragmentshaderLocation = "waterFragment.glsl";
	int locationTransformation;
	int locationProjection;
	int locationView;
	int location_reflactionTexture;
	int location_refractionTexture;

	virtual void getAllUniformLocations() override;
	WaterShader::WaterShader();

	void loadTransformation(glm::fmat4 matrix) {
		Shader::loadMatrixUni(matrix, locationTransformation);
	}

	void loadProjection(glm::fmat4 matrix) {
		Shader::loadMatrixUni(matrix, locationProjection);
	}

	void loadView(Camera& camera) {
		glm::fmat4 ViewMatrix = Mats::createView(camera);
		Shader::loadMatrixUni(ViewMatrix, locationView);
	}
	void connectTectureUnit() {

		Shader::loadIntUni(0, location_reflactionTexture);
		Shader::loadIntUni(1, location_refractionTexture);


	};
};

