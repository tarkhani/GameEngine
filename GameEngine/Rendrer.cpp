#include "Rendrer.h"
#include"GL\glew.h"
#include<iostream>
#include"Mats.h"





void Rendrer::prepare()
{
	glViewport(0, 0, 1920, 1080);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Rendrer::render(entity entityToRender, StaticShader shader)
{
    textureModel ModelToRender = entityToRender.texturemodel;
	RawModel rawmodel = ModelToRender.getRawModel();
	ModelTexture texturemodel = ModelToRender.getTexture();

	glBindVertexArray(rawmodel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glm::mat4 transformationMatrix = Mats::createTransformation(entityToRender.position, entityToRender.rotx, entityToRender.roty, entityToRender.rotz, entityToRender.scale);
	shader.loadTransformation(transformationMatrix);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturemodel.getTextureid());
    glDrawElements(GL_TRIANGLES, rawmodel.getIndexcount(), GL_UNSIGNED_INT, 0);
	CheckGLError();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

Rendrer::Rendrer(StaticShader Shader)
{
	glm::mat4 proj = glm::perspective(70.0f, ((float)1920 / 1080), 0.1f, 100.0f);
	Shader.start();
	Shader.loadProjection(proj);
	Shader.stopProgeram();
}


Rendrer::~Rendrer()
{
}
