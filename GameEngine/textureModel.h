#pragma once
#include"RawModel.h"
#include"ModelTexture.h"
class textureModel
{
public:
	 RawModel rawModel;
	 ModelTexture texture;


	 textureModel(RawModel& rawModel, ModelTexture& texture) : rawModel(rawModel), texture(texture) {};
	 const textureModel(const textureModel& textureModel);
	

	 RawModel getRawModel() {
		return rawModel;
	 };

	 ModelTexture getTexture() {
		return texture;
	};

	 bool operator <( const textureModel& rhs)const
	 {
		return (this->rawModel.getVaoID() < rhs.rawModel.getVaoID());
	 }

};

