#include "Enemy.h"



Enemy::Enemy()
{}

Enemy::Enemy(vector3 ipos) {
	BOMngr = MyBoundingObjectManager::GetInstance();
	name += rand();
	meshManager->LoadModel("Minecraft\\creeper.obj", name);
	vertexList = meshManager->GetVertexList(name);
	BOMngr->setBox(vertexList, name);
	meshManager->SetModelMatrix(glm::translate(pos),name);
	spawn(ipos);
}


Enemy::~Enemy()
{
}

void Enemy::move() {

}

void Enemy::update() {
	if (isAlive)
	{
		move();
		//if its has no health make it dead and remove it from the bounding object vector
		if (health <= 0)
		{isAlive = false;
		BOMngr->removeBO(BO);
		}
	}

}

void Enemy::spawn(vector3 ipos) {
	pos = ipos;
	isAlive = true;
}

void Enemy::render() {

}
