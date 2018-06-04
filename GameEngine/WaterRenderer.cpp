#include "WaterRenderer.h"




WaterRenderer::WaterRenderer(Loader& loader, glm::fmat4 projectionMatrix , WaterFrameBuffer & fbo):fbo(&fbo)
{
	DuDvTextureID = loader.loadTexture(DuDv_Location);
	NormalTextureID = loader.loadTexture(Normal_Location);
	waterShader.start();
	waterShader.connectTectureUnit();
	waterShader.loadProjection(projectionMatrix);
	waterShader.stopProgeram();
	setUpVAO(loader);
}

void WaterRenderer::prepareRender(Camera &camera)
{
	waterShader.start();
	waterShader.loadView(camera);
	glBindVertexArray(quad.getVaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,fbo->reflectionTexture );
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fbo->refractionTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, DuDvTextureID);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, NormalTextureID);
	
}

void WaterRenderer::render(std::list<WaterTile>& waters, Camera & camera, float deltatime)
{
	moveOffSet += waterSpeed*deltatime;
	if (moveOffSet >= 1) moveOffSet = 0;
	
	prepareRender(camera);
	for (std::list<WaterTile>::iterator it1 = waters.begin(); it1 != waters.end(); ++it1)
	{
		glm::fmat4 modelMatrix = Mats::createTransformation(
		glm::fvec3(it1->x, it1->y, it1->z), 0, 0, 0,
		WaterTile::TILE_SIZE);
		waterShader.loadTransformation(modelMatrix);
		waterShader.LoadWaterMoveOffSet(moveOffSet);
		glDrawArrays(GL_TRIANGLES, 0, quad.getIndexcount());

	}
	unbind();
}

void WaterRenderer::unbind()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	waterShader.stopProgeram();
}

void WaterRenderer::setUpVAO(Loader& loader)
{
	glm::vec2 Watervertices[]{ glm::vec2(-1,-1),glm::vec2(-1,1),glm::vec2(1,-1),glm::vec2(1,-1),glm::vec2(-1,1),glm::vec2(1,1) };
	ARRAY<glm::vec2>ARvertices;
	ARvertices.arrayPointer = Watervertices;
	ARvertices.numberOfElements = sizeof(Watervertices) / sizeof(*Watervertices);
	ARvertices.size = sizeof(Watervertices);
	this->quad = loader.loadToVAO(ARvertices);
}

WaterRenderer::~WaterRenderer()
{
}
