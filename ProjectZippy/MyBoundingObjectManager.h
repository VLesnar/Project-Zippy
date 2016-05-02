#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingObjectClass.h"



class MyBoundingObjectManager
{
	static MyBoundingObjectManager* instance;
public:
	int BOnum = 0;
	vector<MyBoundingObjectClass*> boundingObjects;
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
	
	void SetBO(vector<vector3> a_lVectorList, string iname);
	int GetBOCount() { return BOnum; }
	void SetColor(MyBoundingObjectClass* iBO, vector3 color);
	
	//change visibility
	void SetVisibility(MyBoundingObjectClass* iBO);
	void SetVisibility(string iname);
	
	//set visibility for all
	void FlipVisibility();
	void SetVisibility(bool bvis);

	//set the model matrix
	void SetModelMatrix(string iname, matrix4 a_m4ToWorld);

	void RemoveBO(MyBoundingObjectClass * iBO);

	//render all bounding objects
	void Render();
	
	//render a specific bounding object
	void Render(MyBoundingObjectClass* iBO);
	void Render(string iname);

	//returns a bounding object when given a name
	BoundingObjectClass* GetBO(string iname) { }

	void CheckColissions();

	int playerhealth = 3;
	int coreHealth = 5;
};

