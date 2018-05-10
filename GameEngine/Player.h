#pragma once
#include "entity.h"
#include"terrain.h"

class Player :
	public entity
{
public:
	 const float RUN_SPEED = 10;
	 const float TURN_SPEED = 40;
	 const float GRAVITY = -1;
	 const float JumpPower = 0.2;

	 bool onAir = 0;


	float CurrectSpeed=0;
	float CurrectTurnSpeed=0;
	float UpwardsSpeed = 0;

	Player(textureModel &Texturemodel, glm::fvec3 position, float rotx, float roty, float rotz, float scale);
    Player( Player&player);
	~Player();
	void Move(float deltaTime , terrain& terrain);
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void playerJump();


};

