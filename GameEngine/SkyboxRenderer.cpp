#include "SkyboxRenderer.h"




SkyboxRenderer::SkyboxRenderer(Loader & loader, const glm::mat4 & projection)
{

	 glm::vec3 VERTICES []= {
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),

		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),

		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE)
	};

	 ARRAY<glm::vec3> skybox;
	 skybox.arrayPointer = VERTICES;
	 skybox.numberOfElements = sizeof(VERTICES) / sizeof(*VERTICES);
	 skybox.size = sizeof(VERTICES);

	 

	 skyboxModel = loader.loadToVAO(skybox);
	 textureId = loader.loadCubeMap(textureName);
	 skyShader.start();
	 skyShader.loadProjectionMatrix(projection);
	 skyShader.stopProgeram();
}

void SkyboxRenderer::Render(Camera & camera)
{
	skyShader.start();
	skyShader.loadView(camera);
	glBindVertexArray(skyboxModel.getVaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	glDrawArrays(GL_TRIANGLES, 0, skyboxModel.getIndexcount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	skyShader.stopProgeram();
}

SkyboxRenderer::~SkyboxRenderer()
{
}
