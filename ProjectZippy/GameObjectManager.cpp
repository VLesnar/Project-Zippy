#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::SetGO(std::string objectName, std::string modelName, std::string colID, matrix4 intransform)
{
	gameObjects.push_back(new GameObject(objectName, modelName, colID, intransform));
	GOnum++;
}

void GameObjectManager::render()
{
	for (int i = 0; i < GOnum; i++)
	{
		gameObjects[i]->render();
	}
}
