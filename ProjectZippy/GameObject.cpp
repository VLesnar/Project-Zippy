#include "GameObject.h"

GameObject::GameObject(std::string objectName, std::string modelName, std::string colID, matrix4 intransform)
{
	name = objectName;
	m_pMeshMngr->LoadModel(modelName, objectName);
	BOMngr->SetBO(m_pMeshMngr->GetVertexList("objectName"), objectName, colID, this);
	SetModelMatrix(intransform);
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

void GameObject::Render()
{
	m_pMeshMngr->AddInstanceToRenderList(name);
}
