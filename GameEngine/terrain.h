#pragma once
#include<glm\common.hpp>
#include"RawModel.h"
#include"ModelTexture.h"
#include"Loader.h"
#include"TerrainTexture.h"
#include"TerrainTexturePack.h"


class terrain
{
public:
	const static int SIZE = 100;
	const static int VERTEX_COUNT = 128;
	float x, z;
	RawModel Rawmodel;
	TerrainTexturePack terrainTexturePack;
	TerrainTexture blendMap;


	terrain(int grindx,int grindy,Loader& loader, TerrainTexturePack& terrainTexturePack, TerrainTexture& blendMap);
	~terrain();
	RawModel GenrateTerrin(Loader& loader);
};

