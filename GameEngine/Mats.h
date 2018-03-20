#pragma once
#include<glm\gtc\matrix_transform.hpp>
#include<glm\common.hpp>
#include<glm\glm.hpp>
#include"Camera.h"

class Mats
{
public:

	glm::mat4 static createTransformation(glm::vec3 translation, float rx,
		float ry, float rz, float scale);

	glm::mat4 static createView(Camera& camera);
	

	

};