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
	int textureId;
	SkyboxShader skyShader;
	std::string textureName = "";

	SkyboxRenderer(Loader& loader,const glm::mat4 & projection);
	void Render(Camera& camera);
	~SkyboxRenderer();
	
};

