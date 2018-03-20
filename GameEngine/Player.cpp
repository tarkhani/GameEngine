#include "Player.h"




Player::Player(textureModel & texturemodel, glm::fvec3 position, float rotx, float roty, float rotz, float scale)
	:entity::entity(texturemodel, position, rotx, roty, rotz, scale)
{
	
}



Player::~Player()
{
}

void Player::MoveForward()
{
	CurrectSpeed += RUN_SPEED;
}

void Player::MoveBackward()
{
	CurrectSpeed -= RUN_SPEED;
}

void Player::MoveRight()
{
	CurrectTurnSpeed += TURN_SPEED;
}

void Player::MoveLeft()
{
	CurrectTurnSpeed -= TURN_SPEED;
}
