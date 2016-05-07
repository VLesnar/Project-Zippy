#include "EnvironmentManager.h"

EnvironmentManager* EnvironmentManager::instance = nullptr;

EnvironmentManager::EnvironmentManager()
{

}

EnvironmentManager::~EnvironmentManager()
{

}

void EnvironmentManager::SetGO(std::string objectName, std::string modelName, std::string colID, matrix4 intransform)
{
	gameObjects.push_back(new GameObject(objectName, modelName, colID, intransform));
	GOnum++;
}

void EnvironmentManager::Render()
{
	for (int i = 0; i < GOnum; i++)
	{
		gameObjects[i]->Render();
	}
}
