#include "GameObject.h"
#include <iomanip>

//Constructor based on model for static objects
GameObject::GameObject(std::string objectName, std::string modelName, std::string colID, matrix4 intransform)
{
	name = objectName;
	m_pMeshMngr->LoadModel(modelName, objectName);
	BOMngr->SetBO(m_pMeshMngr->GetVertexList(objectName), objectName, colID, this);
	BO = BOMngr->GetBO(BOMngr->GetBOCount() - 1);
	SetModelMatrix(intransform);
	visibility = true;
	acc = vector3(0, 0, 0);
	vel = vector3(0, 0, 0);
}

//Constructor based on radius and other player properties
GameObject::GameObject(std::string objectName, float radius, std::string colID, matrix4 intransform, vector3 inAcc, vector3 inVel)
{
	name = objectName;
	BOMngr->SetBO(radius, objectName, colID, this);
	BO = BOMngr->GetBO(BOMngr->GetBOCount() - 1);
	SetModelMatrix(intransform);

	acc = inAcc;
	vel = inVel;
}

//Destructor
GameObject::~GameObject()
{
	BOMngr->RemoveBO(BO);
	delete BO;
	BOMngr->ReleaseInstance();
	m_pMeshMngr->ReleaseInstance();
}

MyBoundingObjectClass* GameObject::GetBO()
{
	return BO;
}

//Set the matrix of the object and its components
void GameObject::SetModelMatrix(matrix4 intransform)
{
	transform = intransform;
	EstablishModelMatrix();
}

//Translate the object and its components
void GameObject::Translate(vector3 dir)
{
	transform = glm::translate(transform, dir);
	EstablishModelMatrix();
}

//Move the object's model and BO to match itself
void GameObject::EstablishModelMatrix()
{
	m_pMeshMngr->SetModelMatrix(transform, name);
	BOMngr->SetModelMatrix(name, transform);
}

//Move the object based on its acceleration and velocity
void GameObject::MovePhysics(double dt)
{
	vel += acc * static_cast<float>(dt);
	Translate(vel * static_cast<float>(dt));
	EstablishModelMatrix();
}

//Stop the object's velocity, flattening it in a given direction.
void GameObject::HaltVel(vector3 dir)
{
	if (glm::length(dir) > 0)
	{
		vector3 proj = dir * glm::dot(vel, glm::normalize(dir));
		vel -= proj;
	}
}

//Render the object
void GameObject::Render()
{
	if (visibility)
	{
		m_pMeshMngr->AddInstanceToRenderList(name);
	}
		
}
