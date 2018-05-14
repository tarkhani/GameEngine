#include "MousePicker.h"


MousePicker::MousePicker(Camera & camera, GLFWwindow *&window, const glm::mat4 &projectMat) :camera(&camera),projectMat(projectMat),window(window)
{
	viewMat = Mats::createView(camera);
}

glm::fvec3 MousePicker::CalculateRay()
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glm::fvec2 NormalizedDeviceCoord = GetNormalizedDeviceCoord( mouseX, mouseY);
	glm::fvec4 clipCoord = glm::fvec4(NormalizedDeviceCoord.x, NormalizedDeviceCoord.y, -1, 1);
	glm::fvec4 EyeCoord = toEyeCoord(clipCoord);
	glm::fvec3 worldCoord = toWorldCoord(EyeCoord);
	return worldCoord;
		
}

glm::fvec2 MousePicker::GetNormalizedDeviceCoord(float mouseX,float mouseY)
{
	
	int height, width;
	glfwGetWindowSize(window, &width, &height);
	float x = (mouseX / (width / 2)) - 1;
	float y = (mouseX / (height / 2)) - 1;
	return glm::fvec2(x, -y);
}

glm::fvec4 MousePicker::toEyeCoord(glm::fvec4 & clipCoord)
{
	glm::fmat4 inverseProj = glm::inverse(projectMat);
	glm::fvec4 toEyeCoord = inverseProj*clipCoord;
	return glm::fvec4(toEyeCoord.x,toEyeCoord.y,-1,0);

}

glm::fvec3 MousePicker::toWorldCoord(glm::fvec4 & EyeCoord)
{
	glm::fmat4 inverseProj = glm::inverse(viewMat);
	glm::fvec4 WorldCoord = inverseProj*EyeCoord;
	glm::fvec3 temp =glm::fvec3(WorldCoord.x, WorldCoord.y, WorldCoord.z);
	return glm::normalize(temp);
}


void MousePicker::update()
{
	viewMat = Mats::createView(*camera);
	currectRay = CalculateRay();
}
