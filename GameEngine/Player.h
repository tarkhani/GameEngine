#pragma once
#include "entity.h"
class Player :
	public entity
{
public:
	const float RUN_SPEED = 20;
	const float TURN_SPEED = 20;

	float CurrectSpeed=0;
	float CurrectTurnSpeed=0;


	Player(textureModel &texturemodel, glm::fvec3 position, float rotx, float roty, float rotz, float scale);
	~Player();
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();


};

