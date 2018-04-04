#include "Mats.h"


glm::mat4 Mats::createTransformation(glm::vec3& translation, float rx, float ry, float rz, float scale)
{
	glm::mat4 translate = glm::translate(glm::mat4(), translation);
	glm::mat4 rotate = glm::rotate(glm::mat4(), glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(glm::mat4(), glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(glm::mat4(), glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Scale = glm::scale(glm::mat4(), glm::vec3(scale, scale, scale));
	glm::mat4 finalmat4 = translate*rotate*Scale;
	return finalmat4;
}

glm::mat4 Mats::createTransformation(glm::vec3& translation, float rx, float ry, float rz, float scaleX, float scaleY, float scaleZ)
{
	glm::mat4 translate = glm::translate(glm::mat4(), translation);
	glm::mat4 rotate = glm::rotate(glm::mat4(), glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(glm::mat4(), glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(glm::mat4(), glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Scale = glm::scale(glm::mat4(), glm::vec3(scaleX, scaleY, scaleZ));
	glm::mat4 finalmat4 = translate*rotate*Scale;
	return finalmat4;
}

glm::mat4 Mats::createTransformationMatrix(glm::fvec2& translation, glm::fvec2& scale)
{
	glm::vec3 translation3D = glm::vec3(translation,0);
	glm::mat4 translate = glm::translate(glm::mat4(), translation3D);
	glm::vec3 scale3D = glm::vec3(scale, 1);
	glm::mat4 Scale = glm::scale(glm::mat4(), scale3D);
	glm::mat4 Final = translate*Scale;
	return Final;
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

float Mats::barryCentric(glm::fvec3 &p1, glm::fvec3 &p2, glm::fvec3 &p3, glm::fvec2 &pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
