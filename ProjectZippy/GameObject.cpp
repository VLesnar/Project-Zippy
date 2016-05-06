#include "GameObject.h"

GameObject::GameObject(std::string objectName, std::string modelName, std::string colID, matrix4 intransform)
{
	name = objectName;
	m_pMeshMngr->LoadModel(modelName, objectName);
	BOMngr->SetBO(m_pMeshMngr->GetVertexList("objectName"), objectName, colID);
	setModelMatrix(intransform);
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
