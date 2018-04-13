#pragma once
#include<glm\common.hpp>
class Light
{
public:
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec3 attenuation=glm::vec3(1.0,0.0, 0.0);
	
		
	Light(glm::vec3 position,glm::vec3 colour,glm::vec3 attenuation);
	Light(glm::vec3 position, glm::vec3 colour);
	Light(const Light& light) :position(light.position), colour(light.colour), attenuation(light.attenuation){};
	~Light();
};

