#pragma once
class ModelTexture
{
public:

	ModelTexture(int textureid)
	{
		this->textureid = textureid;
	}
	ModelTexture( ModelTexture&ModelTexture):textureid(ModelTexture.textureid)
	{
	}
	int getTextureid() { return textureid; };

private:

	 int textureid;
};

