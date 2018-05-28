#include "RenderMaster.h"

void RenderMaster::prepare()
{
	glViewport(0, 0, 1920, 1080);
	glClearColor(SkyRed, SkyGreen, SkyBlue, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

RenderMaster::RenderMaster(Loader& loader):rendrer(Staticshader, proj ),terrainRenderer(terrainShader,proj), skyRenderer(loader,proj)
{
}

void RenderMaster::Render(std::vector<Light> & lights, Camera & camera, Player&player,float deltaTime, float TimeOfDay, glm::fvec4 &  Culling_plane)
{
	prepare();

	
	terrainShader.start();
	terrainShader.loadCullingPlane(Culling_plane);
	terrainShader.loadSkyColor(SkyColor);
	terrainShader.loadView(camera);
	terrainShader.loadLight(lights);
	terrainRenderer.render(terrains);
	terrainShader.stopProgeram();

	Staticshader.start();
	Staticshader.loadCullingPlane(Culling_plane);
	Staticshader.loadSkyColor(SkyColor);
	Staticshader.loadView(camera);
	Staticshader.loadLight(lights);
	rendrer.render(entities);
	rendrer.render(player);
	Staticshader.stopProgeram();

	skyRenderer.Render(camera,SkyColor, deltaTime, TimeOfDay);

}

void RenderMaster::ProcessEntity(entity& Entity)
{
	
	textureModel Texturemodel = Entity.texturemodel;
	std::map<textureModel, std::list<entity>>::iterator it =entities.find(Texturemodel);
	if (it != entities.end())
	{
		(it->second).push_back(Entity);
	}
	else {
		
		std::list<entity> Newbatch;
		Newbatch.push_back(Entity);
		entities.insert(std::pair<textureModel, std::list<entity>>(Texturemodel, Newbatch));
	}
	
}

void RenderMaster::ProcessTerrain(terrain & terrain)
{
	terrains.push_back(terrain);
}

void RenderMaster::processWorld(std::list<terrain>& terriansList, std::list<entity>& entitiesList)
{
	for (std::list<entity>::iterator it1 = entitiesList.begin(); it1 != entitiesList.end(); ++it1)
	{
		ProcessEntity(*it1);

	}
	for (std::list<terrain>::iterator it2 = terriansList.begin(); it2 != terriansList.end(); ++it2)
	{
		ProcessTerrain(*it2);
	}
}

void RenderMaster::CleanWorld()
{
	entities.clear();
	terrains.clear();
}

void RenderMaster::CleanUp()
{
	Staticshader.cleanUp();
	terrainShader.cleanUp();
}

void RenderMaster::EnableBackFaceCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void RenderMaster::DisableBackFaceCulling()
{
	glDisable(GL_CULL_FACE);
	
}
