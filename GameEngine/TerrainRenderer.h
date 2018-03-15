#pragma once
#include"TerrainShader.h"
#include"terrain.h"
#include"textureModel.h"
class TerrainRenderer
{
private:

	TerrainShader shader;

public:

	void prepareTerrain(terrain Terrain);
	void unboundTextureModel();
	void LoadTerrainMatrix(terrain Terrain);
	TerrainRenderer(TerrainShader& Shader, const  glm::mat4 &proj);
	void render( std::list<terrain> terrains);
	~TerrainRenderer();
};

