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
	
	void setBox(vector<vector3> a_lVectorList, string iname);
	int getBO() { return BOnum; }
	void setColor(MyBoundingObjectClass* iBO, vector3 color);
	
	//change visibility
	void setVisibility(MyBoundingObjectClass* iBO);
	void setVisibility(string iname);

	//set the model matrix
	void setModelMatrix(string iname, matrix4 a_m4ToWorld);

	
	//render all bounding objects
	void render();
	
	//render a specific bounding object
	void render(MyBoundingObjectClass* iBO);
	void render(string iname);

	void checkColissions();


};

