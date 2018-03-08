#pragma once
#include"RawModel.h"
#include"ModelTexture.h"
class textureModel
{
public:
	 RawModel rawModel;
	 ModelTexture texture;

	 textureModel(RawModel& rawModel, ModelTexture& texture) : rawModel(rawModel), texture(texture) {};
	 textureModel(textureModel& textureModel);

	 RawModel getRawModel() {
		return rawModel;
	 };

	 ModelTexture getTexture() {
		return texture;
	};
};

