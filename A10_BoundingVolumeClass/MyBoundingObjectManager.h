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
	
	void SetBox(vector<vector3> a_lVectorList);
	int GetBO() { return BOnum; }
	void SetColor(MyBoundingObjectClass* iBO, vector3 color);
	void SetVisibility(MyBoundingObjectClass* iBO, bool vis);
	void SetModelMatrix(MyBoundingObjectClass* iBO, matrix4 mat);
	
	//render all bounding objects
	void Render();
	//render a specific bounding object
	void Render(MyBoundingObjectClass* iBO);

	void CheckColissions();


};

