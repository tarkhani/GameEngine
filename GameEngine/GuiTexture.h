#pragma once
#include"glm\common.hpp"
class GuiTexture
{
public:
	int textureID;
	glm::fvec2 position;
	glm::fvec2 scale;
	GuiTexture(int textureID, glm::fvec2 position, glm::fvec2 scale):position(position), scale(scale)
	{
		this->textureID = textureID;
	}

	~GuiTexture()
	{
	}
};

