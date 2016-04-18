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

	static MyBoundingObjectManager* GetInstance() {
		if (instance == nullptr) {
			instance = new MyBoundingObjectManager();
		}
		return instance;
	};
	static MyBoundingObjectManager* ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
		return instance;
	}
	
	void setBox(vector<vector3> a_lVectorList);
	int getBO() { return BOnum; }
	void setColor(MyBoundingObjectClass* iBO, vector3 color);
	void setVisibility(MyBoundingObjectClass* iBO);
	
	//render all bounding objects
	void render();
	//render a specific bounding object
	void render(MyBoundingObjectClass* iBO);

	void checkColissions();


};

