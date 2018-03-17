#pragma once
#include<glm\common.hpp>
#include"RawModel.h"
#include"ModelTexture.h"
#include"Loader.h"


class terrain
{
public:
	const static int SIZE = 100;
	const static int VERTEX_COUNT = 128;
	float x, z;
	RawModel Rawmodel;
	ModelTexture Modeltexture;
	terrain(int grindx,int grindy,Loader& loader,ModelTexture& modelTexture);
	~terrain();
	RawModel GenrateTerrin(Loader& loader);
};

