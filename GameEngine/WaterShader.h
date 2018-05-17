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
};

