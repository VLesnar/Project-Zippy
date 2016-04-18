#include "MyBoundingObjectManager.h"

MyBoundingObjectManager* MyBoundingObjectManager::instance = nullptr;


MyBoundingObjectManager::MyBoundingObjectManager()
{
}


MyBoundingObjectManager::~MyBoundingObjectManager()
{
}

//add a box based on a model
void MyBoundingObjectManager::setBox(vector<vector3> a_lVectorList) {
	boundingObjects.push_back(new MyBoundingObjectClass(a_lVectorList));
	BOnum++;
}

void MyBoundingObjectManager::setColor(MyBoundingObjectClass* iBO, vector3 color) {
	iBO->SetColor(color);
}

void MyBoundingObjectManager::setVisibility(MyBoundingObjectClass* iBO) {
	iBO->SetVisibility();
}

void MyBoundingObjectManager::render(MyBoundingObjectClass* iBO) {
	iBO->Render();
}

void MyBoundingObjectManager::render() {
	for (int i = 0; i < BOnum; i++)
	{
		boundingObjects[i]->Render();
	}

}

void MyBoundingObjectManager::checkColissions() {
	for (int i = 0; i < floor(BOnum/2); i+=2)
	{
		boundingObjects[i]->IsColliding(boundingObjects[i + 1]);
	}

}
