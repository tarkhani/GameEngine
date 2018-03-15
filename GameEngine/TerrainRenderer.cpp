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
	ModelTexture texture = Terrain.Modeltexture;
	glBindVertexArray(rawmodel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureid());
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
