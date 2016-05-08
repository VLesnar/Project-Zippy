#pragma once

#include "RE/ReEng.h"
#include "MyBoundingObjectManager.h"

class Enemy
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
	bool isAlive = false;
	Enemy();
	Enemy(vector3 ipos);
	~Enemy();
	void move(double fTimeSpan);
	void Update(double fTimeSpan);
	void spawn(vector3 ipos);
	void Render();
	void Die();
};

