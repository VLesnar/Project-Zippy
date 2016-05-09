#include "MyOctant.h"

using namespace ReEng;
//  MyOctant
bool MyOctant::m_bHead = true;
void MyOctant::Init(void)
{
	m_v3Position = vector3(0.0f);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_fSize = 0.0f;
	m_nChildCount = 0;
	m_pBOMngr = MyBoundingObjectManager::GetInstance();

	if (m_bHead)
	{
		int nObjectCont = m_pBOMngr->GetBOCount();
		vector3 v3MinG = m_pBOMngr->GetBO(0)->GetMinG();
		vector3 v3MaxG = m_pBOMngr->GetBO(0)->GetMaxG();
		for (uint i = 1; i < nObjectCont; i++)
		{
			vector3 v3Min = m_pBOMngr->GetBO(i)->GetMinG();
			vector3 v3Max = m_pBOMngr->GetBO(i)->GetMaxG();
			//for x
			if (v3MinG.x > v3Min.x)
				v3MinG.x = v3Min.x;
			else if (v3MaxG.x < v3Max.x)
				v3MaxG.x = v3Max.x;

			//for y
			if (v3MinG.y > v3Min.y)
				v3MinG.y = v3Min.y;
			else if (v3MaxG.y < v3Max.y)
				v3MaxG.y = v3Max.y;

			//for z
			if (v3MinG.z > v3Min.z)
				v3MinG.z = v3Min.z;
			else if (v3MaxG.z < v3Max.z)
				v3MaxG.z = v3Max.z;
		}
		m_v3Position = (v3MaxG + v3MinG) / 2.0f;
		float fSizeX = glm::distance(vector3(v3MinG.x, 0, 0), vector3(v3MaxG.x, 0, 0));
		float fSizeY = glm::distance(vector3(0, v3MinG.y, 0), vector3(0, v3MaxG.y, 0));
		float fSizeZ = glm::distance(vector3(0, 0, v3MinG.z), vector3(0, 0, v3MaxG.z));

		m_fSize = fSizeX;
		if (m_fSize < fSizeY)
			m_fSize = fSizeY;
		if (m_fSize < fSizeZ)
			m_fSize = fSizeZ;
	}
}
void MyOctant::Swap(MyOctant& other)
{

}

void MyOctant::Release(void)
{

}

//The big 3
MyOctant::MyOctant() { Init(); }
MyOctant::MyOctant(float a_fSize) { Init(); m_fSize = a_fSize; }
MyOctant::MyOctant(MyOctant const& other)
{

}

MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant() { Release(); };

//Display the octree
void MyOctant::Display(void)
{
	for (uint n = 0; n < m_nChildCount; n++)
	{
		m_pChildren[n].Display();
	}

	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_v3Position) * glm::scale(vector3(m_fSize)), REWHITE, WIRE);
}

//Initiate populating the octree
void MyOctant::InitiatePopulation()
{
	ReleaseChildren();	//BE FREE MY CHILDREN!

						//For each object, populate the octree with it.
	int nObjectCont = m_pBOMngr->GetBOCount();
	for (int i = 0; i < nObjectCont; i++)
	{
		Populate(m_pBOMngr->GetBO(i));
	}
}

//Print the population of each octant in the tree
void MyOctant::PrintPopulation()
{
	if (m_nChildCount > 0)
	{
		for (int i = 0; i < m_nChildCount; i++)
		{
			m_pChildren[i].PrintPopulation();
		}
	}
}

//Populate the octree with a given bO
bool MyOctant::Populate(MyBoundingObjectClass* bO)
{
	vector3 v3MinG = bO->GetMinG();	//Minimum vector of the bO	
	vector3 v3MaxG = bO->GetMaxG();	//Maximum vector of the bO

									//Check if bO is completely within the octant. Return false if it isn't.
									//X-check
	if (v3MinG.x < m_v3Position.x - m_fSize / 2)
	{
		return false;
	}
	if (v3MaxG.x > m_v3Position.x + m_fSize / 2)
	{
		return false;
	}

	//Y-check
	if (v3MinG.y < m_v3Position.y - m_fSize / 2)
	{
		return false;
	}
	if (v3MaxG.y > m_v3Position.y + m_fSize / 2)
	{
		return false;
	}

	//Z-check
	if (v3MinG.z < m_v3Position.z - m_fSize / 2)
	{
		return false;
	}
	if (v3MaxG.z > m_v3Position.z + m_fSize / 2)
	{
		return false;
	}

	//If the bO is in the octant and the octant isn't subdivided subdivide the octant.
	if (m_nChildCount == 0)
	{
		Subdivide();
	}

	//Check if any children contain the current bO or any bO
	bool childrenContainBOThis = false;		//If a child contains this bO
	bool childrenContainBOAny = false;		//If a child contains any bO
	for (int i = 0; i < m_nChildCount; i++)
	{
		if (m_pChildren[i].Populate(bO))
		{
			childrenContainBOThis = true;
			break;
		}
		if (m_pChildren[i].m_lObjects.size() != 0)
		{
			childrenContainBOAny = true;
		}
	}

	//If any of the children contain the bO, this doesn't, so return true;
	if (childrenContainBOThis)
	{
		return true;
	}

	//If no children contain any bOs, clear all children
	if (!childrenContainBOAny)
	{
		m_pChildren = nullptr;
		m_nChildCount = 0;
	}

	//Add the bO to this and return true
	m_lObjects.push_back(bO);
	return true;
}

//Remove a bO from the octant.
bool MyOctant::Remove(MyBoundingObjectClass* bO)
{
	uint objectCount = m_lObjects.size();
	for (int i = 0; i < objectCount; i++)
	{
		if (bO == m_lObjects[i])
		{
			m_lObjects.erase(m_lObjects.begin + 1);
			return true;
		}
	}

	for (int i = 0; i < m_nChildCount; i++)
	{
		if (m_pChildren[i].Remove(bO))
		{
			return true;
		}
	}

	return false;
}

//Clear the octant of unused children
void MyOctant::Clear()
{

}

//Check collisions within the octant and child octants.
void MyOctant::CheckCollisions(std::vector<MyBoundingObjectClass*> bOs)
{
	//Internal collision
	int selfCount = m_lObjects.size();
	for (int j = 0; j < selfCount; j++)
	{
		for (int i = j; i < selfCount; i++)
		{
			if (j != i)
				m_pBOMngr->CheckSingleCollision(m_lObjects[j], m_lObjects[i]);
		}
	}

	//External collision
	int otherCount = bOs.size();
	for (int j = 0; j < otherCount; j++)
	{
		for (int i = j; i < selfCount; i++)
		{
			m_pBOMngr->CheckSingleCollision(bOs[j], m_lObjects[i]);
		}
	}

	std::vector<MyBoundingObjectClass*> combined = bOs;	//All bOs that are down the tree from this octant
	combined.insert(combined.end(), m_lObjects.begin(), m_lObjects.end()); //Generate combined list of bOs

																		   //Recurse into children
	for (int i = 0; i < m_nChildCount; i++)
	{
		m_pChildren[i].CheckCollisions(combined);
	}
}

//Create child octants of this octant.
void MyOctant::Subdivide(void)
{
	m_bHead = false;
	m_pChildren = new MyOctant[8];
	m_nChildCount = 8;
	float fNewSize = this->m_fSize / 2;
	for (uint index = 0; index < 8; index++)
	{
		m_pChildren[index].m_fSize = fNewSize;
		m_pChildren[index].m_v3Position = m_v3Position;
	}
	fNewSize /= 2.0f;

	//for the index 0
	m_pChildren[0].m_v3Position.x += fNewSize;
	m_pChildren[0].m_v3Position.y += fNewSize;
	m_pChildren[0].m_v3Position.z += fNewSize;

	//for the index 1
	m_pChildren[1].m_v3Position.x -= fNewSize;
	m_pChildren[1].m_v3Position.y += fNewSize;
	m_pChildren[1].m_v3Position.z += fNewSize;

	//for the index 2
	m_pChildren[2].m_v3Position.x -= fNewSize;
	m_pChildren[2].m_v3Position.y -= fNewSize;
	m_pChildren[2].m_v3Position.z += fNewSize;

	//for the index 3
	m_pChildren[3].m_v3Position.x += fNewSize;
	m_pChildren[3].m_v3Position.y -= fNewSize;
	m_pChildren[3].m_v3Position.z += fNewSize;

	//for the index 4
	m_pChildren[4].m_v3Position.x += fNewSize;
	m_pChildren[4].m_v3Position.y += fNewSize;
	m_pChildren[4].m_v3Position.z -= fNewSize;

	//for the index 5
	m_pChildren[5].m_v3Position.x -= fNewSize;
	m_pChildren[5].m_v3Position.y += fNewSize;
	m_pChildren[5].m_v3Position.z -= fNewSize;

	//for the index 6
	m_pChildren[6].m_v3Position.x -= fNewSize;
	m_pChildren[6].m_v3Position.y -= fNewSize;
	m_pChildren[6].m_v3Position.z -= fNewSize;

	//for the index 7
	m_pChildren[7].m_v3Position.x += fNewSize;
	m_pChildren[7].m_v3Position.y -= fNewSize;
	m_pChildren[7].m_v3Position.z -= fNewSize;
}

//Release all children
void MyOctant::ReleaseChildren(void)
{
	if (m_pChildren != nullptr)
	{
		delete[] m_pChildren;
		m_pChildren = nullptr;
		m_nChildCount = 0;
	}
}

