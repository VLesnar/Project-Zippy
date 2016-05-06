#ifndef __GAMEOBJECTMANAGER_H_
#define __GAMEOBJECTMANAGER_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "GameObject.h"

class GameObjectManager
{
	static GameObjectManager* instance;
public:
	int GOnum = 0;
	std::vector<GameObject*> gameObjects;
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameObjectManager();
		}
		return instance;
	};

	static GameObjectManager* ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
		return instance;
	};

	void SetGO(std::string objectName, std::string modelName, std::string colID, matrix4 intransform);

	void Render();
};
#endif

