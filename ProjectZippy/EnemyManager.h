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
	float spawnDelay = 0.0f;
	float rotation = 0.0f;
	double fRunTime;
	bool firstSpawn = true;
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	EnemyManager();
	EnemyManager(vector3 position, float rot, float offset);
	
	
	~EnemyManager();


	void Render();
	void Update(double fTimeSpan);
	void Spawn();
};

