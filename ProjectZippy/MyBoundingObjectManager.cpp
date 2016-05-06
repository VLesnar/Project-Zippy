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
			//boundingObjects.erase(boundingObjects.begin + i);	//This breaks stuff
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

void MyBoundingObjectManager::CheckColissions()
{
	for (int i = 0; i < BOnum; i++)
	{
		for (int j = i; j < BOnum; j++)
		{
			if (boundingObjects[i]->GetName() != boundingObjects[j]->GetName())
			{
				if (boundingObjects[i]->IsColliding(boundingObjects[j]))
				{
					boundingObjects[i]->SetColor(RERED);
					boundingObjects[j]->SetColor(RERED);

					// If an enemy collides with the core, subtract a point of health
					if (boundingObjects[i]->GetName() == "Core") {
						coreHealth -= 1;
					}

					break;
				}
				else
				{
					boundingObjects[i]->SetColor(REGREEN);
					boundingObjects[j]->SetColor(REGREEN);
				}
			}
		}	
	}
}
