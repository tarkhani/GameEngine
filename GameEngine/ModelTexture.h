#pragma once
class ModelTexture
{
public:

	float ShineDamper;
	float ReflectionScale;
	ModelTexture();
	ModelTexture(int textureid)
	{
		this->textureid = textureid;
	}
	const ModelTexture( const ModelTexture&ModelTexture):textureid(ModelTexture.textureid)
	{
	}
	int getTextureid() { return textureid; };

private:

	 int textureid;
};

