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



void EnemyManager::render() {
	meshManager->AddSphereToRenderList( glm::translate(position) * glm::scale(vector3(3.0f)), RERED, SOLID);
}
void EnemyManager::spawn() {

}
void EnemyManager::update() {
	render();
}
