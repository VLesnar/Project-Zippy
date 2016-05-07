#ifndef __GAMEOBJECTCLASS_H_
#define __GAMEOBJECTCLASS_H_

#include "RE/ReEng.h"
#include "MyBoundingObjectManager.h"

class MyBoundingObjectManager;

class GameObject
{
protected:
	std::string name;
	matrix4 transform;
	vector3 acc;
	vector3 vel;
	MyBoundingObjectClass* BO = nullptr;
	MyBoundingObjectManager* BOMngr = MyBoundingObjectManager::GetInstance();
	MeshManagerSingleton* m_pMeshMngr = MeshManagerSingleton::GetInstance();
public:
	GameObject(std::string objectName, std::string modelName, std::string colID, matrix4 intransform);
	GameObject(std::string objectName, float radius, std::string colID, matrix4 intransform, vector3 inAcc, vector3 inVel);
	~GameObject();
	void SetModelMatrix(matrix4 intransform);
	virtual void Translate(vector3 dir);
	void EstablishModelMatrix();
	void MovePhysics(double dt);
	void HaltVel(vector3 dir);
	void Render();
};
#endif