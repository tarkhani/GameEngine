#pragma once
#include<glm\gtc\matrix_transform.hpp>
#include<glm\common.hpp>
#include<glm\glm.hpp>
#include"Camera.h"

class Mats
{
public:

	glm::mat4 static createTransformation(glm::vec3& translation, float rx,
		float ry, float rz, float scale);

	glm::mat4 static Mats::createTransformation(glm::vec3& translation, float rx,
		float ry, float rz, float scaleX, float scaleY, float scaleZ);

	glm::mat4 static createTransformationMatrix(glm::fvec2 &translation, glm::fvec2& scale);

	glm::mat4 static createView(Camera& camera);
	glm::mat4 static createSkyView(Camera& camera);

	float static barryCentric(glm::fvec3 &p1, glm::fvec3 &p2, glm::fvec3 &p3, glm::fvec2 &pos);
	

	

};