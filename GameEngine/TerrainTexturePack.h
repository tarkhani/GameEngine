#pragma once
#include"TerrainTexture.h"


class TerrainTexturePack{


public:
	TerrainTexture  BackGroundTextureID;
	TerrainTexture  rTextureID;
	TerrainTexture  gTextureID;
	TerrainTexture  bTextureID;

	TerrainTexturePack(TerrainTexture& BackGroundTextureID, TerrainTexture&  rTextureID, TerrainTexture& gTextureID, TerrainTexture&  bTextureID);
	~TerrainTexturePack();
};

