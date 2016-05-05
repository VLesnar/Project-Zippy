#include "GameObject.h"

GameObject::GameObject(string objectName, string modelName, string colID, matrix4 intransform)
{
	name = objectName;
	transform = intransform;
	m_pMeshMngr->LoadModel(modelName, objectName);
	BOMngr->SetBO(m_pMeshMngr->GetVertexList("objectName"), objectName, colID);
}

GameObject::~GameObject()
{

}

void GameObject::setModelMatrix(matrix4 intransform)
{
	transform = intransform;
	establishModelMatrix();
}

void GameObject::translate(vector3 dir)
{
	transform = glm::translate(transform, dir);
	establishModelMatrix();
}

void GameObject::establishModelMatrix()
{
	m_pMeshMngr->SetModelMatrix(transform, name);
	BOMngr->SetModelMatrix(name, transform);
}

void GameObject::render()
{
	m_pMeshMngr->AddInstanceToRenderList(name);
}
