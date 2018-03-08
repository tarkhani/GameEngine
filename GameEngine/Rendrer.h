#pragma once
#include"RawModel.h"
#include"textureModel.h"
#include"RawModel.h"
#include"entity.h"
#include"StaticShader.h"
class Rendrer
{
public:
	
	void prepare();
	void render(entity entityToRender,StaticShader shader);

	Rendrer(StaticShader Shader);
	~Rendrer();
};

