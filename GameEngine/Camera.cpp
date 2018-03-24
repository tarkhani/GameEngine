#include "Camera.h"



Camera::Camera(Player &player):player(&player)
{
}

Camera::~Camera()
{
}
void Camera::CalculateCameraPosition(float HorizontalDistance, float VerticalDistance)
{
	this->CameraLocation.y = (*player).position.y + VerticalDistance+2;
	float theta = (*player).roty + AngleAroundPlayer;
	float XoffSet = HorizontalDistance*std::sin(glm::radians(theta));
	float ZoffSet= HorizontalDistance*std::cos(glm::radians(theta));
	this->CameraLocation.x = (*player).position.x - XoffSet;
	this->CameraLocation.z = (*player).position.z - ZoffSet;
	this->yaw = 180 - theta;

}
void Camera::Move()
{
	float HorizontalDistance = CalculateHorizontalDistance();
	float VerticalDistance = CalculateVerticalDistance();
	CalculateCameraPosition( HorizontalDistance,  VerticalDistance);
}
void Camera::MoveForward()
{
	
	CameraLocation.z += -Speed;
}

void Camera::MoveBackward()
{

	CameraLocation.z += Speed;
}

void Camera::MoveRight()
{
	CameraLocation.x += Speed;
}

void Camera::MoveLeft()
{
	CameraLocation.x -= Speed;
}

void Camera::MoveUp()
{
	CameraLocation.y += Speed;
}

void Camera::MoveDown()
{
	CameraLocation.y += -Speed;
}
