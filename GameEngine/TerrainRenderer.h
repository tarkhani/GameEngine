#pragma once
#include"TerrainShader.h"
#include"terrain.h"
#include"textureModel.h"
#include"TerrainTexturePack.h"
#include"TerrainTexture.h"



class TerrainRenderer
{
private:

	TerrainShader shader;

public:

	void prepareTerrain(terrain Terrain);
	void BindTerrainTextures(terrain& terrain);
	void unboundTextureModel();
	void LoadTerrainMatrix(terrain Terrain);
	TerrainRenderer(TerrainShader& Shader, const  glm::mat4 &proj);
	void render( std::list<terrain> terrains);
	~TerrainRenderer();
};

