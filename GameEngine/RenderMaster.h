#pragma once
#include<glm\gtc\matrix_transform.hpp>
#include<map>
#include<list>
#include"StaticShader.h"
#include"Rendrer.h"
#include"textureModel.h"
#include"entity.h"
#include"Camera.h"
#include"Light.h"
#include"terrain.h"
#include"TerrainShader.h"
#include"TerrainRenderer.h"
class RenderMaster
{
private:
	StaticShader Staticshader;
	Rendrer rendrer;
	std::map<textureModel, std::list<entity>> entities;

	TerrainShader terrainShader;
	TerrainRenderer terrainRenderer;
	std::list<terrain> terrains;
	void prepare();

public:
	static const glm::mat4 proj;

	RenderMaster::RenderMaster();
	void Render(Light &light, Camera& camera);
	void ProcessEntity(entity& Entity);
	void ProcessTerrain(terrain & terrain);
	void CleanUp() ;
};

