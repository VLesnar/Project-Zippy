#include "Enemy.h"


/*
Enemy::Enemy(vector3 ipos)
{
	BOMngr = MyBoundingObjectManager::GetInstance();
	spawn(ipos);
	name += std::to_string(rand());
	meshManager->LoadModel("Thwomp.obj", name);
	vertexList = meshManager->GetVertexList(name);
	BOMngr->SetBO(vertexList, name, "enem", nullptr);
}
*/
Enemy::~Enemy()
{

}

void Enemy::move(double fTimeSpan)
{
	//cout << "calling update of" << name << endl;
	
	fRunTime += fTimeSpan;
	float flerp = MapValue(fRunTime, 0.0f, 10.0f, 0.0f, 1.0f);
	vector3 v3lerp = glm::lerp(pos, vector3(0,1,0), flerp);
	GameObject::SetModelMatrix(glm::translate(v3lerp));

	/*
	meshManager->SetModelMatrix(glm::translate(v3lerp), name);
	BOMngr->SetModelMatrix(name, meshManager->GetModelMatrix(name));*/
	GameObject::Render();
	

}

void Enemy::Update(double fTimeSpan)
{
	
	if (isAlive)
	{
		move(fTimeSpan);
		//if its has no health make it dead and remove it from the bounding object vector

	}
}

void Enemy::Die() {
	isAlive = false;
	BOMngr->RemoveBO(BO);
}

void Enemy::spawn(vector3 ipos)
{
	fRunTime = 0;
	pos = ipos;
	pos.y = 1;
	isAlive = true;
}
/*
void Enemy::Render() 
{
	//meshManager->AddCubeToRenderList(glm::translate(pos), REBLUE, SOLID);
	//meshManager->AddInstanceToRenderList(name);
	GameObject::Render();
}*/
