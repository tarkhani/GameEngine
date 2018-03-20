#include "Mats.h"


glm::mat4 Mats::createTransformation(glm::vec3 translation, float rx, float ry, float rz, float scale)
{
	glm::mat4 translate = glm::translate(glm::mat4(), translation);
	glm::mat4 rotate = glm::rotate(glm::mat4(), glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(glm::mat4(), glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(glm::mat4(), glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Scale = glm::scale(glm::mat4(), glm::vec3(scale, scale, scale));
	glm::mat4 finalmat4 = translate*rotate*Scale;
	return finalmat4;
}

glm::mat4 Mats::createView(Camera& camera)
{
	glm::mat4 rotate = glm::rotate(glm::mat4(), glm::radians(camera.pitch), glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(glm::mat4(), glm::radians(camera.yaw), glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(glm::mat4(), glm::radians(camera.roll), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec3 cameraNegtive = glm::vec3(camera.CameraLocation.x*-1,camera.CameraLocation.y*-1, camera.CameraLocation.z*-1);
	glm::mat4 cameraNegtiveMatrix = glm::translate(glm::mat4(), cameraNegtive);
	glm::mat4 viewMatrix = rotate*cameraNegtiveMatrix;
	
	return viewMatrix ;
}
