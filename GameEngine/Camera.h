#pragma once
#include"glm\glm.hpp"
#include"Player.h"

class Camera
{
public:

	glm::vec3 CameraLocation = glm::vec3(0, 0, 0);
	float Speed=0.3;
	float pitch=0;
	float yaw=0;
	float roll=0;
	Player *player;
	float DistanceFromPlayer = 10;
	float AngleAroundPlayer = 0;

	float CalculateHorizontalDistance() { return DistanceFromPlayer*std::cos(glm::radians(pitch)); };
	float CalculateVerticalDistance() { return DistanceFromPlayer*std::sin(glm::radians(pitch)); };
	void CalculateCameraPosition(float HorizontalDistance, float VerticalDistance);
	void invertpitch() { pitch*-1; };
	void Move();
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	Camera(Player &player);
	~Camera();
};

