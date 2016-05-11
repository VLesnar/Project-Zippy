#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	CameraManagerSingleton* m_pCameraMngr = CameraManagerSingleton::GetInstance();	//Camera that is centered at the player
	float speed = 10.0f;															//Movement speed of the player
	float jumpPulse = 12.0f;														//Velocity given to the player in jump
public:
	Player() : GameObject(
		"player",
		1.50f,
		"play",
		glm::translate(vector3(0.0f, 2.5f, 15.0f)),
		vector3(0, -20, 0),
		vector3(0, 0, 0))

	{
		//Set the camera position
		m_pCameraMngr->SetPositionTargetAndView(
			vector3(transform[3]),//Camera position
			vector3(0.0f, 2.5f, 0.0f),//What Im looking at
			REAXISY);//What is up
	}
	
	void MoveForward(double dt);	//Move
	void MoveBackwards(double dt);	//Move
	void MoveLeft(double dt);		//Move
	void MoveRight(double dt);		//Move
	void Jump();					//Jump
	void Translate(vector3 dir);	//Translate the player in a direction
	void MovePhysics(double dt);	//Perform physics calculations on the player
};