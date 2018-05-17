#pragma once
#include<list>
#include<glm\common.hpp>
#include"RawModel.h"
#include"WaterShader.h"
#include"Loader.h"
#include"WaterTile.h"
#include"Mats.h"

class WaterRenderer
{
public:

	RawModel quad;
	WaterShader waterShader;


	WaterRenderer(Loader & loader,glm::fmat4 projectionMatrix);
	void prepareRender(Camera& camera);
	void render(std::list<WaterTile>& waters, Camera &camera);
	void unbind();
	void setUpVAO(Loader& loader);
	~WaterRenderer();
};

