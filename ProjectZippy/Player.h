#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	CameraManagerSingleton* m_pCameraMngr = CameraManagerSingleton::GetInstance();
	float speed = 10.0f;
public:
	Player() : GameObject("player", 0.75f, "play", IDENTITY_M4) {}
	
	void MoveForward(double dt);
	void MoveBackwards(double dt);
	void MoveLeft(double dt);
	void MoveRight(double dt);
};