#pragma once

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Enemy.h"

class EnemyManager
{

static EnemyManager* instance;

public:
	std::vector<Enemy*> enemies;
	vector3 position;
	int maxEnemies = 3;
	int numEnemies;
	float spawntime = 5.0f;
	double fRunTime;
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	EnemyManager();
	EnemyManager(vector3 position);
	
	~EnemyManager();


	void Render();
	void Update(double fTimeSpan);
	void Spawn();
};

