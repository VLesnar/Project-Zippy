#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

}

EnemyManager::EnemyManager(vector3 pos)
{
	position = pos;
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

}

void EnemyManager::Update() 
{
	Render();
}
