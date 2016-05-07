#include "GameObject.h"

GameObject::GameObject(std::string objectName, std::string modelName, std::string colID, matrix4 intransform)
{
	name = objectName;
	m_pMeshMngr->LoadModel(modelName, objectName);
	BOMngr->SetBO(m_pMeshMngr->GetVertexList(objectName), objectName, colID, this);
	SetModelMatrix(intransform);

	acc = vector3(0, 0, 0);
	vel = vector3(0, 0, 0);
}

GameObject::GameObject(std::string objectName, float radius, std::string colID, matrix4 intransform, vector3 inAcc, vector3 inVel)
{
	name = objectName;
	BOMngr->SetBO(radius, objectName, colID, this);
	SetModelMatrix(intransform);

	acc = inAcc;
	vel = inVel;
}

GameObject::~GameObject()
{

}

void GameObject::SetModelMatrix(matrix4 intransform)
{
	transform = intransform;
	EstablishModelMatrix();
}

void GameObject::Translate(vector3 dir)
{
	transform = glm::translate(transform, dir);
	EstablishModelMatrix();
}

void GameObject::EstablishModelMatrix()
{
	m_pMeshMngr->SetModelMatrix(transform, name);
	BOMngr->SetModelMatrix(name, transform);
}

void GameObject::MovePhysics(double dt)
{
	vel += acc * static_cast<float>(dt);
	Translate(vel * static_cast<float>(dt));
	EstablishModelMatrix();
}

void GameObject::HaltVel(vector3 dir)
{
	if (glm::length(dir) > 0)
	{
		vector3 proj = dir * glm::dot(vel, glm::normalize(dir));
		vel -= proj;
	}
}

void GameObject::Render()
{
	m_pMeshMngr->AddInstanceToRenderList(name);
}
