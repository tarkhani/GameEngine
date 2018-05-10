#pragma once
#include"RawModel.h"
#include"SkyboxShader.h"
#include"glm\common.hpp"
#include<glm\glm.hpp>
#include"Loader.h"

class SkyboxRenderer
{

private:
	float SIZE=100;
public:

	RawModel skyboxModel;
	int textureId1;
	int textureId2;
	SkyboxShader skyShader;
	std::string textureName1 = "";
	std::string textureName2 = "night";

	SkyboxRenderer(Loader& loader,const glm::mat4 & projection);
	void bindTexture();
	void Render(Camera & camera, glm::vec3 &fogColour, float deltaTime ,float TimeOfDay);
	~SkyboxRenderer();
	
};

