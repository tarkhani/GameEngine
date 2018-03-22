#pragma once
#include "entity.h"
class Player :
	public entity
{
public:
	 const float RUN_SPEED = 300;
	 const float TURN_SPEED = 2000;
	 const float GRAVITY = -5;
	 const float JumpPower = 0.08;
	 float TerrianHeight = 0;

	 bool onAir = 0;


	float CurrectSpeed=0;
	float CurrectTurnSpeed=0;
	float UpwardsSpeed = 0;

	Player(textureModel &texturemodel, glm::fvec3 position, float rotx, float roty, float rotz, float scale);
	~Player();
	void Move(float deltaTime);
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void playerJump();


};

