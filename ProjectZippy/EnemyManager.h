#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Enemy.h"

class EnemyManager
{

static EnemyManager* instance;

public:
	vector<Enemy*> enemies;
	vector3 position;
	int maxEnemies;
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();

	EnemyManager();
	EnemyManager(vector3 position);
	
	~EnemyManager();


	void Render();
	void Update();
	void Spawn();
};

