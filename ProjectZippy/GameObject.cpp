#include "GameObject.h"

GameObject::GameObject(string objectName, string modelName, string colID)
{
	transform = IDENTITY_M4;
	m_pMeshMngr->LoadModel(modelName, objectName);
	BOMngr->SetBO(m_pMeshMngr->GetVertexList("objectName"), objectName, colID);
}

GameObject::~GameObject()
{

}

void GameObject::setModelMatrix(matrix4 transform)
{

}

void GameObject::push(vector3 dir)
{

}
