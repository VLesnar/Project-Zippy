#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

}

EnemyManager::EnemyManager(vector3 pos, float rot, float offset)
{
	
	position = pos;
	rotation = rot;
	spawnDelay = offset;
	fRunTime = 0.0f;
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Render()
{
	meshManager->AddCubeToRenderList( glm::translate(position) * glm::scale(vector3(3.0f)), vector3(0.1176f, 0.8039f, 0.8392f), SOLID);
}

void EnemyManager::Spawn() 
{
	if (numEnemies <= maxEnemies) {
		String name = "Enemy";
		name += std::to_string(rand());
		enemies.push_back(new Enemy(position, name, rotation));
		numEnemies++;
	}
	else {
		for (int i = 0; i < numEnemies; i++)
		{
			if (enemies[i]->getVisibility() == false)
			{
				enemies[i]->spawn(position, rotation);
				break; 
			}
		}
	}
}

void EnemyManager::Update(double fTimeSpan)
{
	fRunTime += fTimeSpan;
	if (fRunTime >= spawntime + spawnDelay)
	{

				Spawn();
				spawntime += spawntime;
				firstSpawn = false;


		
	}

	for (int i = 0; i < numEnemies; i++)
	{
		enemies[i]->Update(fTimeSpan);
	}



	Render();
}
