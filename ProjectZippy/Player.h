#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	CameraManagerSingleton* m_pCameraMngr = CameraManagerSingleton::GetInstance();
	float speed = 10.0f;
public:
	Player() : GameObject(
		"player",
		1.50f,
		"play",
		glm::translate(vector3(0.0f, 2.5f, 15.0f)),
		vector3(0, -10, 0),
		vector3(0, 0, 0))

	{
		//Set the camera position
		m_pCameraMngr->SetPositionTargetAndView(
			vector3(transform[3]),//Camera position
			vector3(0.0f, 2.5f, 0.0f),//What Im looking at
			REAXISY);//What is up
	}
	
	void MoveForward(double dt);
	void MoveBackwards(double dt);
	void MoveLeft(double dt);
	void MoveRight(double dt);
	void Jump();
	void Translate(vector3 dir);
	void MovePhysics(double dt);
};