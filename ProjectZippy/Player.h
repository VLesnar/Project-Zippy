#pragma once
#include "RE\ReEngAppClass.h"

class Player
{
	static Player* instance;
	CameraManagerSingleton* m_pCameraMngr = CameraManagerSingleton::GetInstance();
	float speed = 1.0f;
public:
	Player();
	~Player();

	static Player* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Player();
		}
		return instance;
	};

	static Player* ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
		return instance;
	}

	void MoveForward();
	void MoveBackwards();
	void MoveLeft();
	void MoveRight();
};