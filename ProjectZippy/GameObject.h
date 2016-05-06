#ifndef __GAMEOBJECTCLASS_H_
#define __GAMEOBJECTCLASS_H_

#include "RE/ReEng.h"
#include "MyBoundingObjectManager.h"

class GameObject
{
protected:
	std::string name;
	matrix4 transform;
	MyBoundingObjectClass* BO = nullptr;
	MyBoundingObjectManager* BOMngr = MyBoundingObjectManager::GetInstance();
	MeshManagerSingleton* m_pMeshMngr = MeshManagerSingleton::GetInstance();
public:
	GameObject(std::string objectName, std::string modelName, std::string colID, matrix4 intransform);
	~GameObject();
	void SetModelMatrix(matrix4 intransform);
	void Translate(vector3 dir);
	void EstablishModelMatrix();
	void Render();
};
#endif