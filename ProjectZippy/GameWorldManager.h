/*----------------------------------------------
Programmers: Alexander Bronner, Joseph Horsmann,
Veronica Lesnar, and Steven Siewert
Date: 2016/04
Application: Project Zippy
----------------------------------------------*/
#ifndef __GAMEWORLDMANAGER_H_
#define __GAMEWORLDMANAGER_H_

class GameWorldManager
{
	static GameWorldManager* instance;
public:


	GameWorldManager();
	~GameWorldManager();

	static GameWorldManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameWorldManager();
		}
		return instance;
	};

	static GameWorldManager* ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
		return instance;
	}
};

#endif //__GAMEWORLDMANAGER_H_