#pragma once
#include "RE/ReEng.h"
#include "MyBoundingObjectManager.h"

class GameObject
{
protected:
	string name;
	matrix4 transform;
	MyBoundingObjectClass* BO = nullptr;
	MyBoundingObjectManager* BOMngr = MyBoundingObjectManager::GetInstance();
	MeshManagerSingleton* m_pMeshMngr = MeshManagerSingleton::GetInstance();
public:
	GameObject(string objectName, string modelName, string colID, matrix4 intransform);
	~GameObject();
	void setModelMatrix(matrix4 intransform);
	void translate(vector3 dir);
	void establishModelMatrix();
	void render();
};