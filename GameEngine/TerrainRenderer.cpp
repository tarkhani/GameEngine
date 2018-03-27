#include "TerrainRenderer.h"





TerrainRenderer::TerrainRenderer(TerrainShader & Shader, const glm::mat4 & proj)
{
	this->shader = Shader;
	Shader.start();
	Shader.loadProjection(proj);
	Shader.stopProgeram();
}

void TerrainRenderer::render(std::list<terrain> terrains)
{
	for (std::list<terrain>::iterator it = terrains.begin(); it != terrains.end(); ++it)
	{
		prepareTerrain(*it);
		LoadTerrainMatrix(*it);
		RawModel rawmodel = (*it).Rawmodel;
		glDrawElements(GL_TRIANGLES, rawmodel.getIndexcount(), GL_UNSIGNED_SHORT, 0);


	
		unboundTextureModel();
	}

}

void TerrainRenderer::prepareTerrain(terrain Terrain)
{
	RawModel rawmodel = Terrain.Rawmodel;
	TerrainTexturePack  terrainTexturePack = Terrain.terrainTexturePack;
	glBindVertexArray(rawmodel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	BindTerrainTextures(Terrain);
	shader.loadReflactionAttrib(Terrain.ShineDamper, Terrain.ReflectionScale);
	
}


void  TerrainRenderer::BindTerrainTextures(terrain& terrain){

	TerrainTexturePack terrainTexturePack = terrain.terrainTexturePack;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,terrainTexturePack.BackGroundTextureID.textureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, terrainTexturePack.rTextureID.textureID);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, terrainTexturePack.gTextureID.textureID);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, terrainTexturePack.bTextureID.textureID);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain.blendMap.textureID);


}

void TerrainRenderer::unboundTextureModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::	LoadTerrainMatrix(terrain Terrain)
{
	glm::mat4 transformationMatrix = Mats::createTransformation(glm::vec3(Terrain.x,0, Terrain.z), 0, 0, 0, 1);
	shader.loadTransformation(transformationMatrix);
}

TerrainRenderer::~TerrainRenderer()
{
}
