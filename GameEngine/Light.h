#pragma once
#include<glm\common.hpp>
class Light
{
public:
	glm::vec3 position;
	glm::vec3 colour;
		
	Light(glm::vec3 position,glm::vec3 colour);
	Light(const Light& light) :position(light.position), colour(light.colour) {};
	~Light();
};

