#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include<glm\common.hpp>
#include"Mats.h"
class MousePicker
{
private:

	glm::fvec2 GetNormalizedDeviceCoord(float mouseX, float mouseY);
	glm::fvec4 toEyeCoord(glm::fvec4 &clipCoord);
	glm::fvec3 toWorldCoord(glm::fvec4 &EyeCoord);


public:

	glm::fvec3 currectRay;
	Camera *camera;
	glm::fmat4 viewMat;
	glm::fmat4 projectMat;
	float ScreenWidth;
	float ScreenHeight;
	GLFWwindow *window;

	MousePicker::MousePicker(Camera & camera, GLFWwindow *&window,const glm::mat4 &projectMat);
	glm::fvec3 CalculateRay();
	void update();

};

