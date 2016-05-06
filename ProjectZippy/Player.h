#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	CameraManagerSingleton* m_pCameraMngr = CameraManagerSingleton::GetInstance();
	float speed = 1.0f;
public:
	Player() : GameObject("player", 0.75f, "play", IDENTITY_M4) {}
	
	void MoveForward();
	void MoveBackwards();
	void MoveLeft();
	void MoveRight();
};