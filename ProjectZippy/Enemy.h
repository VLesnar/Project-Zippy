#pragma once

#include "RE/ReEng.h"
#include "MyBoundingObjectManager.h"
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	
	int health = 10;
	vector3 pos;
	MyBoundingObjectManager* BOMngr = nullptr;
	MyBoundingObjectClass* BO = nullptr;
	std::string name = "enemy";
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	SystemSingleton* sytem = SystemSingleton::GetInstance();
	float fRunTime;
	std::vector<vector3> vertexList;
public:
	Enemy(vector3 ipos, String name) : GameObject(
		name,
		"thwomp.obj",
		"enem",
		glm::translate(ipos)
		)
	{
		pos = ipos;
		pos.y = 1;
		isAlive = true;
	}

	bool isAlive = false;
	//Enemy(vector3 ipos);
	~Enemy();
	void move(double fTimeSpan);
	void Update(double fTimeSpan);
	void spawn(vector3 ipos);
	//void Render();
	void Die();
};

