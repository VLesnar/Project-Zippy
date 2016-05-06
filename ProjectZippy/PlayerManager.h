#pragma once
#include "RE\ReEngAppClass.h"
#include "GameObject.h"

class PlayerManager
{
	static PlayerManager* instance;
	CameraManagerSingleton* m_pCameraMngr = CameraManagerSingleton::GetInstance();
	float speed = 1.0f;
public:
	PlayerManager();
	~PlayerManager();

	static PlayerManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new PlayerManager();
		}
		return instance;
	};

	static PlayerManager* ReleaseInstance()
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