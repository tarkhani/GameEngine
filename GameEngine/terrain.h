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
	char * HightMapAddress;
	float x, z;
	RawModel Rawmodel;
	TerrainTexturePack terrainTexturePack;
	TerrainTexture blendMap;
	float ShineDamper;
	float ReflectionScale;
	int length = 0;
	float ** heights = NULL;

	terrain(int grindx,int grindy,Loader& loader, TerrainTexturePack& terrainTexturePack, TerrainTexture& blendMap, char * HightMapAddress);
	float getHeightOfTerrian(float worldX, float worldZ);
	terrain(const terrain & orginal);
	~terrain();
	RawModel GenrateTerrin(Loader& loader, char * HightMapAddress);

};

