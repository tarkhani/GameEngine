#pragma once
#include<list>
#include"Loader.h"
#include"RawModel.h"
#include"GuiTexture.h"
#include"GuiShader.h"

class GuiRenderer
{
	
public:

	RawModel quad;
	GuiShader guiShader;
	GuiRenderer( Loader &loader);
	void render(std::list<GuiTexture>& guis);
	void cleanUp();
	~GuiRenderer();
};

