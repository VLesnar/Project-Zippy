#pragma once
#include "RE/ReEng.h"
#include "MyBoundingObjectManager.h"

class GameObject
{
protected:
	matrix4 transform;
	MyBoundingObjectClass* BO = nullptr;
	MyBoundingObjectManager* BOMngr = MyBoundingObjectManager::GetInstance();
	MeshManagerSingleton* m_pMeshMngr = MeshManagerSingleton::GetInstance();
public:
	GameObject(string objectName, string modelName, string colID);
	~GameObject();
	void setModelMatrix(matrix4 transform);
	void push(vector3 dir);
};