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
	if (numEnemies <= maxEnemies) {
		String name = "Enemy";
		name += std::to_string(rand());
		enemies.push_back(new Enemy(position, name));
		numEnemies++;
	}
	else {
		for (int i = 0; i < numEnemies; i++)
		{
			if (enemies[i]->isAlive == false)
			{
				enemies[i]->spawn(position);
				break; 
			}
		}
	}
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
