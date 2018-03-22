#pragma once
#include"glm\glm.hpp"
class Camera
{
public:

	glm::vec3 CameraLocation = glm::vec3(0, 7, 17);
	float Speed=0.3;
	float pitch=0;
	float yaw=0;
	float roll=0;


	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	Camera();
	~Camera();
};

