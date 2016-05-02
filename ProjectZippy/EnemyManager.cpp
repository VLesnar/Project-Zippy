#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

}

EnemyManager::EnemyManager(vector3 pos)
{
	position = pos;
	fRunTime = 0.0f;
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Render()
{
	meshManager->AddSphereToRenderList( glm::translate(position) * glm::scale(vector3(3.0f)), RERED, SOLID);
}

void EnemyManager::Spawn() 
{
	enemies.push_back(new Enemy(position));
	numEnemies++;
}

void EnemyManager::Update(double fTimeSpan)
{
	fRunTime += fTimeSpan;
	if (fRunTime >= spawntime)
	{
		
		Spawn();
		spawntime += spawntime;
	}

	for (int i = 0; i < numEnemies; i++)
	{
		enemies[i]->Update(fTimeSpan);
	}



	Render();
}
