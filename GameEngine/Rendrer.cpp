#include "Rendrer.h"
#include"RenderMaster.h"




void Rendrer::prepareTextureModel( textureModel textureModel)
{

	
	RawModel rawmodel = textureModel.getRawModel();
	ModelTexture texturemodel = textureModel.getTexture();

	if (texturemodel.tansparent)
	{
		
		RenderMaster::DisableBackFaceCulling();
	}
	glBindVertexArray(rawmodel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturemodel.getTextureid());
	shader.loadReflactionAttrib(texturemodel.ShineDamper, texturemodel.ReflectionScale);
	shader.loadFakeLightning(texturemodel.FakeLightning);
	
}

void Rendrer::unboundTextureModel()
{
	RenderMaster::EnableBackFaceCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Rendrer::prepareInstance(entity entity)
{
	if (entity.scaleX!=1|| entity.scaleY != 1 || entity.scaleZ != 1  )
	{
		glm::mat4 transformationMatrix = Mats::createTransformation(entity.position, entity.rotx, entity.roty, entity.rotz, entity.scaleX, entity.scaleY, entity.scaleZ
		);
		shader.loadTransformation(transformationMatrix);
		shader.loadNumberOfRows(entity.texturemodel.texture.NumberofRow);
		glm::vec2 xyoffset = glm::vec2(entity.getTextureXoffset(), entity.getTextureYoffset());
		shader.loadxyOffset(xyoffset);
	}
	else {
		glm::mat4 transformationMatrix = Mats::createTransformation(entity.position, entity.rotx, entity.roty, entity.rotz, entity.Totalscale);
		shader.loadTransformation(transformationMatrix);
		shader.loadNumberOfRows(entity.texturemodel.texture.NumberofRow);
		glm::vec2 xyoffset = glm::vec2(entity.getTextureXoffset(), entity.getTextureYoffset());
		shader.loadxyOffset(xyoffset);
	}
}

void Rendrer::render(std::map<textureModel, std::list<entity>> entities)
{
	for (std::map<textureModel, std::list<entity>>::iterator it1 = entities.begin(); it1 != entities.end(); ++it1) {

		prepareTextureModel(it1->first);
		std::list<entity> entityGroup = it1->second;
		for ( std::list<entity>::iterator it2 = entityGroup.begin(); it2 != entityGroup.end(); ++it2)
		{
			 prepareInstance(*it2);
			 RawModel rawmodel = (*it2).texturemodel.getRawModel();
			 glDrawElements(GL_TRIANGLES, rawmodel.getIndexcount(), GL_UNSIGNED_SHORT, 0);

		}
		
	}
	unboundTextureModel();
}

void Rendrer::render(entity & entity)
{
	prepareTextureModel(entity.texturemodel);
	prepareInstance(entity);
	RawModel rawmodel = (entity).texturemodel.getRawModel();
	glDrawElements(GL_TRIANGLES, rawmodel.getIndexcount(), GL_UNSIGNED_SHORT, 0);
}


Rendrer::Rendrer(StaticShader& Shader,const glm::mat4 &proj)
{
	this->shader = Shader;
	Shader.start();
	Shader.loadProjection(proj);
	Shader.stopProgeram();
}


Rendrer::~Rendrer()
{
}
