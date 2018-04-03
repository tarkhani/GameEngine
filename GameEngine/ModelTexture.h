#pragma once
class ModelTexture
{
public:

	float ShineDamper;
	float ReflectionScale;
	bool tansparent = false;
	bool FakeLightning = false;
	int NumberofRow = 1;
	ModelTexture();
	ModelTexture(int textureid)
	{
		this->textureid = textureid;
	}
	const ModelTexture( const ModelTexture&ModelTexture):textureid(ModelTexture.textureid),
		ShineDamper(ModelTexture.ShineDamper), ReflectionScale(ModelTexture.ReflectionScale),
		tansparent(ModelTexture.tansparent), FakeLightning(ModelTexture.FakeLightning),
		NumberofRow(ModelTexture.NumberofRow)
	{
	}
	int getTextureid() { return textureid; };

private:

	 int textureid;
};

