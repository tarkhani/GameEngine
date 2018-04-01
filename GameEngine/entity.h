#pragma once
#include"textureModel.h"
#include<glm\glm.hpp>

class entity
{

public:
	textureModel texturemodel;
	glm::fvec3 position;
	float rotx=0;
	float roty=0;
	float rotz=0;
	float Totalscale=1;
	float scaleX=1;
	float scaleY=1;
	float scaleZ=1;
	void increasePosition(float dx,float dy,float dz);
	void increaseRotation(float dx, float dy, float dz);
	
	entity(textureModel &texturemodel,glm::fvec3 position,float rotx, float roty, float rotz, float Totalscale);
	entity(textureModel &texturemodel, glm::fvec3 position, float rotx, float roty, float rotz, float scaleX, float scaleY, float scaleZ);
	~entity();


};


