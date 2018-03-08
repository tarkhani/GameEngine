#include "Camera.h"



Camera::Camera()
{
}

Camera::~Camera()
{
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
