#ifndef __EnvironmentManager_H_
#define __EnvironmentManager_H_

#include <SFML\Graphics.hpp>
#include "GameObject.h"

class EnvironmentManager
{
	static EnvironmentManager* instance;
public:
	int GOnum = 0;
	std::vector<GameObject*> gameObjects;
	EnvironmentManager();
	~EnvironmentManager();

	static EnvironmentManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new EnvironmentManager();
		}
		return instance;
	};

	static EnvironmentManager* ReleaseInstance()
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

