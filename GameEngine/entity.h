#pragma once
#include"textureModel.h"
#include<glm\glm.hpp>

class entity
{

public:
	textureModel texturemodel;
	glm::fvec3 position;
	float rotx;
	float roty;
	float rotz;
	float scale;
	void increasePosition(float dx,float dy,float dz);
	void increaseRotation(float dx, float dy, float dz);
	
	entity(textureModel &texturemodel,glm::fvec3 position,float rotx, float roty, float rotz, float scale);
	~entity();


};


