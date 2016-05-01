#include "MyBoundingObjectManager.h"

MyBoundingObjectManager* MyBoundingObjectManager::instance = nullptr;


MyBoundingObjectManager::MyBoundingObjectManager()
{
}


MyBoundingObjectManager::~MyBoundingObjectManager()
{
}

//add a box based on a model
void MyBoundingObjectManager::setBox(vector<vector3> a_lVectorList, string iname) {
	boundingObjects.push_back(new MyBoundingObjectClass(a_lVectorList, iname));
	BOnum++;
}

void MyBoundingObjectManager::setColor(MyBoundingObjectClass* iBO, vector3 color) {
	iBO->SetColor(color);
}

//set visible by passing in an object or a string
void MyBoundingObjectManager::setVisibility(MyBoundingObjectClass* iBO) { iBO->SetVisibility();}
void MyBoundingObjectManager::setVisibility(string iname) {
	for (int i = 0; i < BOnum; i++){if (boundingObjects[i]->GetName()==iname){boundingObjects[i]->SetVisibility();}}
}
//change the visibility of all of them
void MyBoundingObjectManager::setVisibility(bool bvis) {
	for (int i = 0; i < BOnum; i++)
	{
		boundingObjects[i]->SetVisibility(bvis);
	}
}

void MyBoundingObjectManager::setVisibility() {
	for (int i = 0; i < BOnum; i++)
	{
		boundingObjects[i]->SetVisibility();
	}
}
//set the model matrix
void MyBoundingObjectManager::setModelMatrix(string iname, matrix4 a_m4ToWorld) {
	for (int i = 0; i < BOnum; i++)
	{
		if (boundingObjects[i]->GetName() == iname) { boundingObjects[i]->SetModelMatrix(a_m4ToWorld); }
	}
}
//removes a bounding object from the vector used for enemies
void MyBoundingObjectManager::removeBO(MyBoundingObjectClass* iBO) {
	for (int i = 0; i < BOnum; i++) {
		if (boundingObjects[i] == iBO)
		{
			//boundingObjects.erase(boundingObjects.begin + i);	//This breaks stuff
		}
	}
}


void MyBoundingObjectManager::render(MyBoundingObjectClass* iBO) {
	iBO->Render();
}

void MyBoundingObjectManager::render(string iname) {
	for (int i = 0; i < BOnum; i++)
	{
		if (boundingObjects[i]->GetName() == iname) { boundingObjects[i]->Render(); }
	}
}

void MyBoundingObjectManager::render() {
	for (int i = 0; i < BOnum; i++)
	{
		boundingObjects[i]->Render();
	}

}

void MyBoundingObjectManager::checkColissions() {
	for (int i = 0; i < BOnum; i++)
	{
		for (int j = i; j < BOnum; j++)
		{
			if (boundingObjects[i]->GetName() != boundingObjects[j]->GetName()) {
				if (boundingObjects[i]->IsColliding(boundingObjects[j]))
				{
					boundingObjects[i]->SetColor(RERED);
					boundingObjects[j]->SetColor(RERED);
					//cout << boundingObjects[i]->GetName() << " is colliding with " << boundingObjects[j]->GetName() << endl;
					break;
				}
				else
				{
					boundingObjects[i]->SetColor(REGREEN);
					boundingObjects[j]->SetColor(REGREEN);
				}
			}
		}
		
	}

}
