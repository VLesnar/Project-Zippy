#include "MyBoundingObjectManager.h"

MyBoundingObjectManager* MyBoundingObjectManager::instance = nullptr;


MyBoundingObjectManager::MyBoundingObjectManager()
{
}


MyBoundingObjectManager::~MyBoundingObjectManager()
{
}

//add a box based on a model
void MyBoundingObjectManager::SetBox(vector<vector3> a_lVectorList) {
	boundingObjects.push_back(new MyBoundingObjectClass(a_lVectorList));
	BOnum++;
}

void MyBoundingObjectManager::SetColor(MyBoundingObjectClass* iBO, vector3 color) {
	iBO->SetColor(color);
}

void MyBoundingObjectManager::SetVisibility(MyBoundingObjectClass* iBO, bool vis) {
	iBO->SetVisibility(vis);
}

void MyBoundingObjectManager::SetModelMatrix(MyBoundingObjectClass* iBO, matrix4 mat) {
	iBO->SetModelMatrix(mat);
}

void MyBoundingObjectManager::Render(MyBoundingObjectClass* iBO) {
	iBO->Render();
}

void MyBoundingObjectManager::Render() {
	for (int i = 0; i < BOnum; i++)
	{
		boundingObjects[i]->Render();
	}

}

void MyBoundingObjectManager::CheckColissions() {
	for (int i = 0; i < floor(BOnum/2); i+=2)
	//for (int i = 0; i < BOnum - 1; i++)
	{
		boundingObjects[i]->IsColliding(boundingObjects[i + 1]);
	}

}
