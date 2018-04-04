#include "GuiRenderer.h"
#include"Mats.h"






GuiRenderer::GuiRenderer(Loader& loader)
{
	glm::fvec2 vertices[]{glm::vec2(-1,1),glm::vec2(-1,-1),glm::vec2(1,1),glm::vec2(1,-1) };
	ARRAY<glm::fvec2>ARvertices;
	ARvertices.arrayPointer = vertices;
	ARvertices.numberOfElements = sizeof(vertices) / sizeof(*vertices);
	ARvertices.size = sizeof(vertices);
	this->quad = loader.loadToVAO(ARvertices);

}

void GuiRenderer::render(std::list<GuiTexture> &guis)
{
	guiShader.start();
	glBindVertexArray(this->quad.getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	for (std::list<GuiTexture>::iterator it = guis.begin(); it != guis.end(); ++it) {

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, it->textureID);
		glm::mat4 transformation = Mats::createTransformationMatrix(it->position, it->scale);
		guiShader.loadTransformation(transformation);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getIndexcount());

	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	guiShader.stopProgeram();
}

void GuiRenderer::cleanUp()
{

	guiShader.cleanUp();
}

GuiRenderer::~GuiRenderer()
{
}
