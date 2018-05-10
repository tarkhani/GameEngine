#pragma once
#include"Shader.h"
#include"Camera.h"
#include"Mats.h"
class SkyboxShader :public Shader
{
public:

	char* vertaxShaderLocation = "skyboxVertexShader.txt";
	char* fragmentshaderLocation = "skyboxFragmentShader.txt";
	int location_CubeMap1;
	int location_CubeMap2;
	int location_projectionMatrix;
	int location_viewMatrix;
	int location_fogColour;
	int location_blendFactor;
	const float ROTATE_SPEED = 1.0f;
	float rotation = 0.0f;

	SkyboxShader();
	virtual void getAllUniformLocations() override;

	 void loadProjectionMatrix(const glm::mat4& matrix) {
		Shader::loadMatrixUni(matrix, location_projectionMatrix);
	}

	 void loadView(Camera& camera,float deltatime) {
		 glm::fmat4 ViewMatrix = Mats::createSkyView(camera);
		 rotation += ROTATE_SPEED*deltatime;
		 glm::fmat4 temp= glm::rotate(glm::mat4(), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		 ViewMatrix = ViewMatrix*temp;
		 Shader::loadMatrixUni(ViewMatrix, location_viewMatrix);
	 }

	 void loadfogColour(glm::vec3 & fogColour) {
		 Shader::loadvectorUni(fogColour, location_fogColour);
	 }

	 void loadBlendFactor(float BlendFactor) {
		 Shader::loadFloatUni(BlendFactor, location_blendFactor);
	 }
	 void ConnectTextureUnit() {
		 Shader::loadIntUni(0, location_CubeMap1);
		 Shader::loadIntUni(1, location_CubeMap2);
	 }
	~SkyboxShader();
};

