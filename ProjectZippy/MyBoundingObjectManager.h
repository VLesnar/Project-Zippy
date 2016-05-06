#ifndef __MYBOUNDINGOBJECTMANAGER_H_
#define __MYBOUNDINGOBJECTMANAGER_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingObjectClass.h"

class MyBoundingObjectManager
{
	static MyBoundingObjectManager* instance;
public:
	int BOnum = 0;
	int playerhealth = 3;
	int coreHealth = 5;
	std::vector<MyBoundingObjectClass*> boundingObjects;
	MyBoundingObjectManager();
	~MyBoundingObjectManager();

	static MyBoundingObjectManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new MyBoundingObjectManager();
		}
		return instance;
	};

	static MyBoundingObjectManager* ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
		return instance;
	}
	
	void SetBO(std::vector<vector3> a_lVectorList, std::string iname, std::string colID, GameObject* parent);
	int GetBOCount() { return BOnum; }
	void SetColor(MyBoundingObjectClass* iBO, vector3 color);
	
	//change visibility
	void SetVisibility(MyBoundingObjectClass* iBO);
	void SetVisibility(std::string iname);
	
	//set visibility for all
	void FlipVisibility();
	void SetVisibility(bool bvis);

	//set the model matrix
	void SetModelMatrix(std::string iname, matrix4 a_m4ToWorld);

	void RemoveBO(MyBoundingObjectClass * iBO);

	//render all bounding objects
	void Render();
	
	//render a specific bounding object
	void Render(MyBoundingObjectClass* iBO);
	void Render(std::string iname);

	//returns a bounding object when given a name
	BoundingObjectClass* GetBO(std::string iname) { }

	void CheckColissions();
};
#endif

