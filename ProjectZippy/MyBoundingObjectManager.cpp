#include "MyBoundingObjectManager.h"

MyBoundingObjectManager* MyBoundingObjectManager::instance = nullptr;


MyBoundingObjectManager::MyBoundingObjectManager()
{

}


MyBoundingObjectManager::~MyBoundingObjectManager()
{

}

//add a box based on a model
void MyBoundingObjectManager::SetBO(std::vector<vector3> a_lVectorList, std::string name, std::string colID, GameObject* parent)
{
	boundingObjects.push_back(new MyBoundingObjectClass(a_lVectorList, name, colID, parent));
	BOnum++;
}

void MyBoundingObjectManager::SetBO(float radius, std::string name, std::string colID, GameObject* parent)
{
	boundingObjects.push_back(new MyBoundingObjectClass(radius, name, colID, parent));
	BOnum++;
}

//Set the color of a box
void MyBoundingObjectManager::SetColor(MyBoundingObjectClass* iBO, vector3 color)
{
	iBO->SetColor(color);
}

//set visible by passing in an object or a std::string
void MyBoundingObjectManager::SetVisibility(MyBoundingObjectClass* iBO) { iBO->FlipVisibility();}
void MyBoundingObjectManager::SetVisibility(std::string iname)
{
	for (int i = 0; i < BOnum; i++){if (boundingObjects[i]->GetName()==iname){boundingObjects[i]->FlipVisibility();}}
}

//change the visibility of all BOs to a value.
void MyBoundingObjectManager::SetVisibility(bool bvis)
{
	for (int i = 0; i < BOnum; i++)
	{
		boundingObjects[i]->SetVisibility(bvis);
	}
}

//Flip the visibility of all BOs
void MyBoundingObjectManager::FlipVisibility()
{
	for (int i = 0; i < BOnum; i++)
	{
		boundingObjects[i]->FlipVisibility();
	}
}

//set the model matrix of a BO.
void MyBoundingObjectManager::SetModelMatrix(std::string iname, matrix4 a_m4ToWorld)
{
	for (int i = 0; i < BOnum; i++)
	{
		if (boundingObjects[i]->GetName() == iname)
		{
			boundingObjects[i]->SetModelMatrix(a_m4ToWorld);
		}
	}
}

//removes a bounding object from the vector used for enemies
void MyBoundingObjectManager::RemoveBO(MyBoundingObjectClass* iBO)
{
	for (int i = 0; i < BOnum; i++)
	{
		if (boundingObjects[i] == iBO)
		{
			boundingObjects.erase(boundingObjects.begin() + i);
		}
	}
}

void MyBoundingObjectManager::Render(MyBoundingObjectClass* iBO)
{
	iBO->Render();
}

void MyBoundingObjectManager::Render(std::string iname)
{
	for (int i = 0; i < BOnum; i++)
	{
		if (boundingObjects[i]->GetName() == iname) { boundingObjects[i]->Render(); }
	}
}

void MyBoundingObjectManager::Render()
{
	for (int i = 0; i < BOnum; i++)
	{
		boundingObjects[i]->Render();
	}
}

MyBoundingObjectClass* MyBoundingObjectManager::GetBO(uint a_nIndex)
{
	if (a_nIndex < GetBOCount())
		return boundingObjects[a_nIndex];

	return nullptr;
}

MyBoundingObjectClass* MyBoundingObjectManager::GetBO(std::string a_sName) {
	for (uint i = 0; i < boundingObjects.size(); i++) {
		if (boundingObjects[i]->GetName() == a_sName) {
			return boundingObjects[i];
		}
	}
}



std::vector<MyBoundingObjectClass*> MyBoundingObjectManager::GetBOsByID(std::string a_id)
{
	std::vector<MyBoundingObjectClass*> tempBOs;

	for (uint i = 0; i < boundingObjects.size(); i++)
	{
		if (boundingObjects[i]->GetColID() == a_id)
		{
			tempBOs.push_back(boundingObjects[i]);
		}
	}

	return tempBOs;
}

void MyBoundingObjectManager::CheckColissions()
{
	for (int i = 0; i < BOnum; i++)
	{
		for (int j = i; j < BOnum; j++)
		{
			if (boundingObjects[i]->GetColID() != boundingObjects[j]->GetColID())
			{
				CheckSingleCollision(boundingObjects[i], boundingObjects[j]);
			}
		}	
	}
}

void MyBoundingObjectManager::CheckSingleCollision(MyBoundingObjectClass* obj1, MyBoundingObjectClass* obj2)
{
	if (
		(obj1->GetColID() == "play" && obj2->GetColID() == "wall") ||
		(obj1->GetColID() == "wall" && obj2->GetColID() == "play"))
	{
		MyBoundingObjectClass* bOPlay = obj1->GetColID() == "play" ? obj1 : obj2;
		MyBoundingObjectClass* bOWall = obj1->GetColID() == "wall" ? obj1 : obj2;

		if (bOWall->IsCollidingABB(bOPlay))
		{
			if (bOWall->IsCollidingSOB(bOPlay))
			{
				bOWall->SetColor(RERED);
			}
			else
			{
				bOWall->SetColor(REGREEN);
			}
		}
		else
		{
			bOWall->SetColor(REGREEN);
		}
	}

	if (
		(obj1->GetColID() == "play" && obj2->GetColID() == "core") ||
		(obj1->GetColID() == "core" && obj2->GetColID() == "play"))
	{
		MyBoundingObjectClass* bOPlay = obj1->GetColID() == "play" ? obj1 : obj2;
		MyBoundingObjectClass* bOWall = obj1->GetColID() == "core" ? obj1 : obj2;

		if (bOWall->IsCollidingABB(bOPlay))
		{
			if (bOWall->IsCollidingSOB(bOPlay))
			{
				bOWall->SetColor(RERED);
			}
			else
			{
				bOWall->SetColor(REGREEN);
			}
		}
		else
		{
			bOWall->SetColor(REGREEN);
		}
	}

	if (
		(obj1->GetColID() == "play" && obj2->GetColID() == "enem") ||
		(obj1->GetColID() == "enem" && obj2->GetColID() == "play"))
	{
		MyBoundingObjectClass* bOPlay = obj1->GetColID() == "play" ? obj1 : obj2;
		MyBoundingObjectClass* bOEnem = obj1->GetColID() == "enem" ? obj1 : obj2;

		if (bOEnem->IsCollidingABB(bOPlay))
		{
			if (bOEnem->IsCollidingSOB(bOPlay))
			{
				bOEnem->SetColor(RERED);
			}
			else
			{
				bOEnem->SetColor(REGREEN);
			}
		}
		else
		{
			bOEnem->SetColor(REGREEN);
		}
	}

	if (
		(obj1->GetColID() == "enem" && obj2->GetColID() == "core") ||
		(obj1->GetColID() == "core" && obj2->GetColID() == "enem"))
	{
		if (obj1->IsCollidingABB(obj2))
		{
			//coreHealth -= 1;
		}
	}
}
