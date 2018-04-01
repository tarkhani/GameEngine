#include "entity.h"






void entity::increasePosition(float dx, float dy, float dz)
{
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void entity::increaseRotation(float dx, float dy, float dz)
{
	this->rotx += dx;
	this->roty += dy;
	this->rotz += dz;
}

entity::entity(textureModel &texturemodel, glm::fvec3 position, float rotx, float roty, float rotz, float Totalscale):texturemodel(texturemodel)
{
	this->position = position;
	this->rotx = rotx;
	this->roty = roty;
	this->rotz = rotz;
	this->Totalscale = Totalscale;
}

entity::entity(textureModel & texturemodel, glm::fvec3 position, float rotx, float roty, float rotz, float scaleX, float scaleY, float scaleZ) :texturemodel(texturemodel)
{
	this->position = position;
	this->rotx = rotx;
	this->roty = roty;
	this->rotz = rotz;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

entity::~entity()
{
}
