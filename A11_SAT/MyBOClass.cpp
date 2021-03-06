#include "MyBOClass.h"

//  MyBOClass
void MyBOClass::Init(void)
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3CenterG = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);

	m_fRadius = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

//Swap values with another BO
void MyBOClass::Swap(MyBOClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);

	std::swap(m_v3NAxis, other.m_v3NAxis);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}

//The big 3 (CONSTRUCTOR
MyBOClass::MyBOClass(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f; //with the max and the min we calculate the center
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f; //we calculate the distance between all the values of min and max vectors
	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;
}

//The big 3 (COPY CONSTRUCTOR)
MyBOClass::MyBOClass(MyBOClass const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;

	m_fRadius = other.m_fRadius;

	m_pMeshMngr = other.m_pMeshMngr;
}

//The big 3 (COPY ASSIGNMENT OPERATOR)
MyBOClass& MyBOClass::operator=(MyBOClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBOClass temp(other);
		Swap(temp);
	}
	return *this;
}

//Destructor
MyBOClass::~MyBOClass() { Release(); };

//Release the pointers in the BO
void MyBOClass::Release(void) {/* No pointers allocated yet */ }

//Set the model matrix and corner points based on the given to-global coordinates.
void MyBOClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	//Do nothing if the to-global coordinates haven't changed.
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;

	//Calculate the vertex that makes the Object
	m_v3Corners[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	m_v3Corners[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	m_v3Corners[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	m_v3Corners[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	m_v3Corners[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	m_v3Corners[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	m_v3Corners[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	m_v3Corners[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);

	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		m_v3Corners[nVertex] = vector3(m_m4ToWorld * vector4(m_v3Corners[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxG = m_v3MinG = m_v3Corners[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinG.x > m_v3Corners[nVertex].x) //If min is larger than current
			m_v3MinG.x = m_v3Corners[nVertex].x;
		else if (m_v3MaxG.x < m_v3Corners[nVertex].x)//if max is smaller than current
			m_v3MaxG.x = m_v3Corners[nVertex].x;

		if (m_v3MinG.y > m_v3Corners[nVertex].y) //If min is larger than current
			m_v3MinG.y = m_v3Corners[nVertex].y;
		else if (m_v3MaxG.y < m_v3Corners[nVertex].y)//if max is smaller than current
			m_v3MaxG.y = m_v3Corners[nVertex].y;

		if (m_v3MinG.z > m_v3Corners[nVertex].z) //If min is larger than current
			m_v3MinG.z = m_v3Corners[nVertex].z;
		else if (m_v3MaxG.z < m_v3Corners[nVertex].z)//if max is smaller than current
			m_v3MaxG.z = m_v3Corners[nVertex].z;
	}

	m_v3CenterG = (m_v3MinG + m_v3MaxG) / 2.0f;
	m_v3HalfWidthG = (m_v3MaxG - m_v3MinG) / 2.0f; //we calculate the distance between all the values of min and max vectors
	//m_fRadius = glm::distance(m_v3CenterG, m_v3MaxG);

	m_v3NAxis[0] = vector3(m_m4ToWorld * vector4(1.0f, 0.0f, 0.0f, 1.0f)) - vector3(m_m4ToWorld[3]);
	m_v3NAxis[1] = vector3(m_m4ToWorld * vector4(0.0f, 1.0f, 0.0f, 1.0f)) - vector3(m_m4ToWorld[3]);
	m_v3NAxis[2] = vector3(m_m4ToWorld * vector4(0.0f, 0.0f, 1.0f, 1.0f)) - vector3(m_m4ToWorld[3]);
}

//Accessors
float MyBOClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBOClass::GetModelMatrix(void) { return m_m4ToWorld; }
vector3 MyBOClass::GetCenterLocal(void) { return m_v3Center; }
vector3 MyBOClass::GetCenterGlobal(void) { return m_v3CenterG; }
vector3 MyBOClass::GetHalfWidth(void) { return m_v3HalfWidth; }
vector3 MyBOClass::GetHalfWidthG(void) { return m_v3HalfWidthG; }
vector3 MyBOClass::GetMin(void) { return m_v3Min; }
vector3 MyBOClass::GetMax(void) { return m_v3Max; }
vector3 MyBOClass::GetMinG(void) { return m_v3MinG; }
vector3 MyBOClass::GetMaxG(void) { return m_v3MaxG; }

//Display methods
void MyBOClass::DisplaySphere(vector3 a_v3Color)
{
	m_pMeshMngr->AddSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(vector3(m_fRadius * 2.0f)), a_v3Color, WIRE);
}
void MyBOClass::DisplayOriented(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(m_v3HalfWidth * 2.0f), a_v3Color, WIRE);
}
void MyBOClass::DisplayReAlligned(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, m_v3CenterG) *
		glm::scale(m_v3HalfWidthG * 2.0f), a_v3Color, WIRE);
}

//Collision methods
bool MyBOClass::IsCollidingSOB(MyBOClass * a_otherObj)
{
	vector3 sphereRelative;
	vector3 distVect;
	vector3 pythagComp;

	for (int j = 0; j < 3; j++)	//For each axis
	{
		distVect[j] = abs(glm::dot(a_otherObj->m_v3CenterG - m_v3CenterG, m_v3NAxis[j])) - m_v3HalfWidth[j];
		pythagComp = distVect;
		if (pythagComp[j] < 0)
			pythagComp[j] = 0;
	}

	if (glm::length(pythagComp) > a_otherObj->m_fRadius)
	{
		return false;
	}
	else
	{
		int index = 0;
		float min = FLT_MAX;
		for (int j = 0; j < 3; j++)	//For each axis
		{
			if (distVect[j] < min)
			{
				min = distVect[j];
				index = j;
			}
		}
		vector3 push = m_v3NAxis[index] * distVect[index];
		//a_otherObj->m_v3CenterG += push;
	}

	return true;
}

bool MyBOClass::IsCollidingSAT(MyBOClass* a_otherObj)
{
	float projPointsT[15][8];	//This's projected points	
	float projPointsO[15][8];	//Other's projected points

	//Projections to Objects A's axis
	for (int j = 0; j < 3; j++)	//For each axis
	{
		for (int i = 0; i < 8; i++)	//For each point
		{
			projPointsT[j][i] = glm::dot(m_v3Corners[i], m_v3NAxis[j]);				//Set projected point for this
			projPointsO[j][i] = glm::dot(a_otherObj->m_v3Corners[i], m_v3NAxis[j]);	//Set projected point for other
		}
	}

	//Projections to Object B's axis
	for (int j = 3; j < 6; j++)	//For each axis
	{
		for (int i = 0; i < 8; i++)	//For each point
		{
			projPointsT[j][i] = glm::dot(m_v3Corners[i], a_otherObj->m_v3NAxis[j - 3]);				//Set projected point for this
			projPointsO[j][i] = glm::dot(a_otherObj->m_v3Corners[i], a_otherObj->m_v3NAxis[j - 3]);	//Set projected point for other
		}
	}

	//Cross product axis projections
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 3; j++)
		{
			vector3 temp = glm::cross(m_v3NAxis[k], a_otherObj->m_v3NAxis[j]);	//Cross product
			if (glm::length(temp) > 0)
			{
				temp = glm::normalize(temp); //Normalized cross product
			}
			for (int i = 0; i < 8; i++)	//For each point
			{
				projPointsT[k * 3 + j][i] = glm::dot(m_v3Corners[i], temp);				//Set projected point for this
				projPointsO[k * 3 + j][i] = glm::dot(a_otherObj->m_v3Corners[i], temp);	//Set projected point for other
			}
		}
	}

	//Check
	for (int j = 0; j < 15; j++)	//For each set of projections, see if a plane exists between objects.
	{
		float maxT = projPointsT[j][0];	//Max for this
		float minT = projPointsT[j][0];	//Min for this
		float minO = projPointsO[j][0];	//Min for other
		float maxO = projPointsO[j][0];	//Max for other

		//set mins and maxs
		for (int i = 1; i < 8; i++)	//For each point
		{
			if (projPointsT[j][i] > maxT)
				maxT = projPointsT[j][i];

			if (projPointsT[j][i] < minT)
				minT = projPointsT[j][i];

			if (projPointsO[j][i] > maxO)
				maxO = projPointsO[j][i];

			if (projPointsO[j][i] < minO)
				minO = projPointsO[j][i];
		}

		//If there exists a plane, return false, no collision
		if (minO > maxT || minT > maxO)
		{
			return false;
		}
	}

	return true;
}

bool MyBOClass::IsColliding(MyBOClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For Objects we will assume they are colliding, unless at least one of the following conditions is not met
	*/

	//first check the bounding sphere, if that is not colliding we can guarantee that there are no collision
	if ((m_fRadius + a_pOther->m_fRadius) < glm::distance(m_v3CenterG, a_pOther->m_v3CenterG))
		return false;

	//next check the axis-aligned bounding boxes.

	//Check for X
	if (m_v3MaxG.x < a_pOther->m_v3MinG.x)
		return false;
	if (m_v3MinG.x > a_pOther->m_v3MaxG.x)
		return false;

	//Check for Y
	if (m_v3MaxG.y < a_pOther->m_v3MinG.y)
		return false;
	if (m_v3MinG.y > a_pOther->m_v3MaxG.y)
		return false;

	//Check for Z
	if (m_v3MaxG.z < a_pOther->m_v3MinG.z)
		return false;
	if (m_v3MinG.z > a_pOther->m_v3MaxG.z)
		return false;

	//Finally, check the oriented bounding boxes.

	if (!IsCollidingSAT(a_pOther))
	{
		return false;
	}

	return true;
}