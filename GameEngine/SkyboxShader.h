#pragma once
#include"Shader.h"
#include"Camera.h"
#include"Mats.h"
class SkyboxShader :public Shader
{
public:

	char* vertaxShaderLocation = "skyboxVertexShader.txt";
	char* fragmentshaderLocation = "skyboxFragmentShader.txt";
	int location_projectionMatrix;
	int location_viewMatrix;

	SkyboxShader();
	virtual void getAllUniformLocations() override;

	 void loadProjectionMatrix(const glm::mat4& matrix) {
		Shader::loadMatrixUni(matrix, location_projectionMatrix);
	}
	 void loadView(Camera& camera) {
		 glm::fmat4 ViewMatrix = Mats::createSkyView(camera);
		 Shader::loadMatrixUni(ViewMatrix, location_viewMatrix);
	 }
	~SkyboxShader();
};

