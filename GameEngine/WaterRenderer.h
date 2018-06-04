#pragma once
#include<list>
#include<glm\common.hpp>
#include"RawModel.h"
#include"WaterShader.h"
#include"Loader.h"
#include"WaterTile.h"
#include"Mats.h"
#include"WaterFrameBuffer.h"

class WaterRenderer
{
public:

	char* DuDv_Location = "./res/dudv.png";
	char* Normal_Location = "./res/WaterNormal.png";
	GLuint DuDvTextureID;
	GLuint NormalTextureID;
	RawModel quad;
	WaterShader waterShader;
	WaterFrameBuffer *fbo;
	const float  waterSpeed = 0.02;
	float moveOffSet = 0;


	WaterRenderer(Loader & loader,glm::fmat4 projectionMatrix,WaterFrameBuffer & fbo);
	void prepareRender(Camera& camera);
	void render(std::list<WaterTile>& waters, Camera &camera, float deltatime);
	void unbind();
	void setUpVAO(Loader& loader);
	~WaterRenderer();
};

