#include "Player.h"




Player::Player(textureModel & texturemodel, glm::fvec3 position, float rotx, float roty, float rotz, float scale)
	:entity::entity(texturemodel, position, rotx, roty, rotz, scale)
{
	
}



Player::~Player()
{
}

void Player::Move(float deltaTime)
{
	this->increaseRotation(0,CurrectTurnSpeed*deltaTime,0);
	float distance = CurrectSpeed*deltaTime;
	float dx =  distance * std::sin(glm::radians(roty));
	float dz =  distance * std::cos(glm::radians(roty));
	this->increasePosition(dx, 0, dz);
	UpwardsSpeed += GRAVITY*deltaTime;
	this->increasePosition(0, UpwardsSpeed, 0);
	if (this->position.y<TerrianHeight)
	{
		UpwardsSpeed = 0;
		this->position.y = TerrianHeight;
		this->onAir = false;
	}

	
}

void Player::MoveForward()
{
	CurrectSpeed = RUN_SPEED;
}

void Player::MoveBackward()
{
	CurrectSpeed = -RUN_SPEED;
}

void Player::MoveRight()
{
	CurrectTurnSpeed = -TURN_SPEED;
}

void Player::MoveLeft()
{
	CurrectTurnSpeed = TURN_SPEED;
}

void Player::playerJump()
{
	if (onAir)
	{

	}
	else {
		UpwardsSpeed = JumpPower;
		onAir = 1;
	}
}
