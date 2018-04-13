#include "Light.h"



Light::Light(glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation) :position(position), colour(colour), attenuation(attenuation)
{
}

Light::Light(glm::vec3 position, glm::vec3 colour) : position(position), colour(colour)
{
}


Light::~Light()
{
}
