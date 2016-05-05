#pragma once
#include "RE/ReEng.h"
#include "MyBoundingObjectManager.h"
using namespace std;

class Enemy
{
private:
	bool isAlive = false;
	int health = 10;
	vector3 pos;
	MyBoundingObjectManager* BOMngr = nullptr;
	MyBoundingObjectClass* BO = nullptr;
	string name = "enemy";
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	SystemSingleton* sytem = SystemSingleton::GetInstance();
	float fRunTime;
	std::vector<vector3> vertexList;
public:
	Enemy();
	Enemy(vector3 ipos);
	~Enemy();
	void getHit(int dmg) { health = health - dmg; }
	int getHealth() { return health; }
	void move(double fTimeSpan);
	void Update(double fTimeSpan);
	void spawn(vector3 ipos);
	void Render();
};
