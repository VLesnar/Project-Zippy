#ifndef __GAMEOBJECTCLASS_H_
#define __GAMEOBJECTCLASS_H_

#include "RE/ReEng.h"
#include "MyBoundingObjectManager.h"

class MyBoundingObjectManager;

class GameObject
{
protected:
	std::string name;	//Name of the game object
	matrix4 transform;	//Transform of the object
	vector3 acc;		//Acceleration of the object
	vector3 vel;		//Velocity of the object
	MyBoundingObjectClass* BO = nullptr;										//Bounding object of the player
	MyBoundingObjectManager* BOMngr = MyBoundingObjectManager::GetInstance();	//Bom singleton
	MeshManagerSingleton* m_pMeshMngr = MeshManagerSingleton::GetInstance();	//Mm singleton
	bool visibility;
public:
	GameObject(std::string objectName, std::string modelName, std::string colID, matrix4 intransform);						//Constructor based on model for static objects
	GameObject(std::string objectName, float radius, std::string colID, matrix4 intransform, vector3 inAcc, vector3 inVel);	//Constructor based on radius and other player properties
	~GameObject();								//Destructor
	MyBoundingObjectClass* GetBO();
	void SetModelMatrix(matrix4 intransform);	//Set the matrix of the object and its components
	virtual void Translate(vector3 dir);		//Translate the object and its components
	void EstablishModelMatrix();				//Move the object's model and BO to match itself
	void MovePhysics(double dt);				//Move the object based on its acceleration and velocity
	void HaltVel(vector3 dir);					//Stop the object's velocity, flattening it in a given direction.
	void setVisibility(bool bvis) { visibility = bvis; }
	bool getVisibility() { return visibility; }
	
	void Render();								//Render the object
};
#endif