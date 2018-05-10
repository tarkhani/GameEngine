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
	 textureId1 = loader.loadCubeMap(textureName1);
	 textureId2 = loader.loadCubeMap(textureName2);
	 skyShader.start();
	 skyShader.ConnectTextureUnit();
	 skyShader.loadProjectionMatrix(projection);
	 skyShader.stopProgeram();
}

void SkyboxRenderer::bindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId2);
	
}

void SkyboxRenderer::Render(Camera & camera,glm::vec3 &fogColour,float deltaTime, float TimeOfDay)
{
	skyShader.start();
	skyShader.loadView(camera, deltaTime);
	skyShader.loadfogColour(fogColour);
	glBindVertexArray(skyboxModel.getVaoID());
	glEnableVertexAttribArray(0);
	bindTexture();
	skyShader.loadBlendFactor(TimeOfDay);
	glDrawArrays(GL_TRIANGLES, 0, skyboxModel.getIndexcount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	skyShader.stopProgeram();
}

SkyboxRenderer::~SkyboxRenderer()
{
}
