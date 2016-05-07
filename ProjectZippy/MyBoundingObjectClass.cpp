/*-----------------------------------------------
Programmers: Alexander Bronner, Joseph Horsmann
	Veronica Lesnar, & Steven Siewert
MyBoundingObjectClass.h - Contains methods to
	create sphere and box colliders
-----------------------------------------------*/
#include "MyBoundingObjectClass.h"

// Allocates member fields
void MyBoundingObjectClass::Init()
{
	m_vList = std::vector<vector3>();
	m_v3Max = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Center = vector3(0.0f);
	m_fRadius = 0.0f;
	m_v3Size = vector3(0.0f);
	m_bList = std::vector<vector3>();
	m_v3ChangingSize = vector3(0.0f);
	m_v3ChangingMin = vector3(0.0f);
	m_v3ChangingMax = vector3(0.0f);
	m_m4ToWorld = IDENTITY_M4;
	m_bIsVisible = true;
}

// Changes the object's contents with another
void MyBoundingObjectClass::Swap(MyBoundingObjectClass& other)
{
	std::swap(m_vList, other.m_vList);
	std::swap(m_v3Max, other.m_v3Max);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_fRadius, other.m_fRadius);
	std::swap(m_v3Size, other.m_v3Size);
	std::swap(m_bList, other.m_bList);
	std::swap(m_v3ChangingSize, other.m_v3ChangingSize);
	std::swap(m_v3ChangingMin, other.m_v3ChangingMin);
	std::swap(m_v3ChangingMax, other.m_v3ChangingMax);
	std::swap(m_m4ToWorld, other.m_m4ToWorld);
}

// Deallocates member fields
void MyBoundingObjectClass::Release()
{

}

// Constructor
MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> a_lVectorList, std::string iname, std::string incolID, GameObject* inparent)
{
	SubConstruct(a_lVectorList, iname, incolID, inparent);
}

//Overloaded constructor
MyBoundingObjectClass::MyBoundingObjectClass(float radius, std::string iname, std::string incolID, GameObject * inparent)
{
	std::vector<vector3> a_lVectorList = std::vector<vector3>();

	a_lVectorList.push_back(vector3(0, radius, 0));
	a_lVectorList.push_back(vector3(0, -radius, 0));

	SubConstruct(a_lVectorList, iname, incolID, inparent);
}

//Sub constructor called by both constructors
void MyBoundingObjectClass::SubConstruct(std::vector<vector3> a_lVectorList, std::string iname, std::string incolID, GameObject* inparent)
{
	//Set parent object
	parent = inparent;

	// Store the list of vertices from the model
	m_vList = a_lVectorList;

	//store the name of the object
	name = iname;

	//store the collision ID
	colID = incolID;

	//set the visibility
	m_bIsVisible = true;

	// Calculate the max, min, center, radius, and size
	uint nVertexCount = m_vList.size();

	// Checks to make sure there are vertices stored
	if (nVertexCount > 0) {
		m_v3Max = m_vList[0];
		m_v3Min = m_vList[0];
	}

	// Set the max and the min vectors
	for (uint i = 0; i < nVertexCount; i++)
	{
		vector3 tempVect = m_vList[i];

		// X
		if (tempVect.x > m_v3Max.x)
			m_v3Max.x = tempVect.x;
		else if (tempVect.x < m_v3Min.x)
			m_v3Min.x = tempVect.x;

		// Y
		if (tempVect.y > m_v3Max.y)
			m_v3Max.y = tempVect.y;
		else if (tempVect.y < m_v3Min.y)
			m_v3Min.y = tempVect.y;

		// Z
		if (tempVect.z > m_v3Max.z)
			m_v3Max.z = tempVect.z;
		else if (tempVect.z < m_v3Min.z)
			m_v3Min.z = tempVect.z;
	}

	m_v3Center = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3Center, m_v3Max);
	m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	m_v3Size.z = glm::distance(vector3(0.0f, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));

	m_bList.push_back(vector3(m_v3Size.x, m_v3Size.y, m_v3Size.z));
	m_bList.push_back(vector3(m_v3Size.x, m_v3Size.y, -m_v3Size.z));
	m_bList.push_back(vector3(m_v3Size.x, -m_v3Size.y, m_v3Size.z));
	m_bList.push_back(vector3(m_v3Size.x, -m_v3Size.y, -m_v3Size.z));
	m_bList.push_back(vector3(-m_v3Size.x, m_v3Size.y, m_v3Size.z));
	m_bList.push_back(vector3(-m_v3Size.x, m_v3Size.y, -m_v3Size.z));
	m_bList.push_back(vector3(-m_v3Size.x, -m_v3Size.y, m_v3Size.z));
	m_bList.push_back(vector3(-m_v3Size.x, -m_v3Size.y, -m_v3Size.z));

	SetChangingCubeSize();
}

// Copy Constructor
MyBoundingObjectClass::MyBoundingObjectClass(MyBoundingObjectClass const& other)
{
	m_vList = other.m_vList;
	m_v3Max = other.m_v3Max;
	m_v3Min = other.m_v3Min;
	m_v3Center = other.m_v3Center;
	m_fRadius = other.m_fRadius;
	m_v3Size = other.m_v3Size;
	m_bList = other.m_bList;
	m_v3ChangingSize = other.m_v3ChangingSize;
	m_v3ChangingMin = other.m_v3ChangingMin;
	m_v3ChangingMax = other.m_v3ChangingMax;
	m_m4ToWorld = other.m_m4ToWorld;
}

// Copy Assignment Operator
MyBoundingObjectClass& MyBoundingObjectClass::operator=(MyBoundingObjectClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBoundingObjectClass temp(other);
		Swap(temp);
	}

	return *this;
}

// Destructor
MyBoundingObjectClass::MyBoundingObjectClass()
{
	Release();
}

// Gets the center in global coordinates
vector3 MyBoundingObjectClass::GetGlobalCenter()
{
	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));
}

// Gets the matrix of the center in global coordinates
matrix4 MyBoundingObjectClass::GetGlobalCenterMatrix(void)
{
	return glm::translate(m_m4ToWorld, m_v3Center);
}

// Gets the object's radius
float MyBoundingObjectClass::GetRadius()
{
	return m_fRadius;
}

// Gets the object's bounding box's size
vector3 MyBoundingObjectClass::GetSize()
{
	return m_v3Size;
}

// Gets the object's axis-aligned bounding box's size
vector3 MyBoundingObjectClass::GetChangingSize()
{
	return m_v3ChangingSize;
}

// Changes the size of the axis-aligned bounding box
void MyBoundingObjectClass::SetChangingCubeSize()
{
	for (int i = 0; i < m_bList.size(); i++)
	{
		vector3 tempVect = vector3(GetGlobalCenterMatrix() * vector4(m_bList[i], 1.0f)) - vector3(GetGlobalCenterMatrix()[3]);

		if (tempVect.x > m_v3ChangingMax.x)
			m_v3ChangingMax.x = tempVect.x;
		else if (tempVect.x < m_v3ChangingMin.x)
			m_v3ChangingMin.x = tempVect.x;

		if (tempVect.y > m_v3ChangingMax.y)
			m_v3ChangingMax.y = tempVect.y;
		else if (tempVect.y < m_v3ChangingMin.y)
			m_v3ChangingMin.y = tempVect.y;

		if (tempVect.z > m_v3ChangingMax.z)
			m_v3ChangingMax.z = tempVect.z;
		else if (tempVect.z < m_v3ChangingMin.z)
			m_v3ChangingMin.z = tempVect.z;
	}

	m_v3ChangingMin /= 2;
	m_v3ChangingMax /= 2;

	m_v3ChangingSize.x = glm::distance(vector3(m_v3ChangingMin.x, 0.0, 0.0), vector3(m_v3ChangingMax.x, 0.0, 0.0));
	m_v3ChangingSize.y = glm::distance(vector3(0.0, m_v3ChangingMin.y, 0.0), vector3(0.0, m_v3ChangingMax.y, 0.0));
	m_v3ChangingSize.z = glm::distance(vector3(0.0, 0.0, m_v3ChangingMin.z), vector3(0.0, 0.0, m_v3ChangingMax.z));
}

// Gets the object's matrix
matrix4 MyBoundingObjectClass::GetModelMatrix()
{
	return m_m4ToWorld;
}

// Sets the object's matrix
void MyBoundingObjectClass::SetModelMatrix(matrix4 a_m4ToWorld)
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

	m_v3NAxis[0] = glm::normalize(vector3(m_m4ToWorld * vector4(1.0f, 0.0f, 0.0f, 1.0f)) - vector3(m_m4ToWorld[3]));
	m_v3NAxis[1] = glm::normalize(vector3(m_m4ToWorld * vector4(0.0f, 1.0f, 0.0f, 1.0f)) - vector3(m_m4ToWorld[3]));
	m_v3NAxis[2] = glm::normalize(vector3(m_m4ToWorld * vector4(0.0f, 0.0f, 1.0f, 1.0f)) - vector3(m_m4ToWorld[3]));
}

bool MyBoundingObjectClass::IsCollidingSOB(MyBoundingObjectClass * a_otherObj)
{
	vector3 distVect;

	for (int j = 0; j < 3; j++)	//For each axis
	{
		distVect[j] = abs(glm::dot(a_otherObj->m_v3CenterG - m_v3CenterG, m_v3NAxis[j])) - m_v3ChangingSize[j] / 2;
		if (distVect[j] < 0)
			distVect[j] = 0;
	}

	if (glm::length(distVect) > a_otherObj->m_fRadius)
	{
		return false;
	}

	return true;
}

// Collision methods
bool MyBoundingObjectClass::IsCollidingSAT(MyBoundingObjectClass* a_otherObj)
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

	// Projections to Object B's axis
	for (int j = 3; j < 6; j++)	//For each axis
	{
		for (int i = 0; i < 8; i++)	//For each point
		{
			projPointsT[j][i] = glm::dot(m_v3Corners[i], a_otherObj->m_v3NAxis[j - 3]);				//Set projected point for this
			projPointsO[j][i] = glm::dot(a_otherObj->m_v3Corners[i], a_otherObj->m_v3NAxis[j - 3]);	//Set projected point for other
		}
	}

	// Cross product axis projections
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 3; j++)
		{
			vector3 temp = glm::cross(m_v3NAxis[k], a_otherObj->m_v3NAxis[j]);	//Cross product
			if (glm::length(temp) > 0)
			{
				temp = glm::normalize(temp); // Normalized cross product
			}
			for (int i = 0; i < 8; i++)	// For each point
			{
				projPointsT[k * 3 + j][i] = glm::dot(m_v3Corners[i], temp);				// Set projected point for this
				projPointsO[k * 3 + j][i] = glm::dot(a_otherObj->m_v3Corners[i], temp);	// Set projected point for other
			}
		}
	}

	// Check
	for (int j = 0; j < 15; j++)	// For each set of projections, see if a plane exists between objects.
	{
		float maxT = projPointsT[j][0];	// Max for this
		float minT = projPointsT[j][0];	// Min for this
		float minO = projPointsO[j][0];	// Min for other
		float maxO = projPointsO[j][0];	// Max for other

										// set mins and maxs
		for (int i = 1; i < 8; i++)	// For each point
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

		// If there exists a plane, return false, no collision
		if (minO > maxT || minT > maxO)
		{
			return false;
		}
	}

	return true;
}

// Checks to see if two objects are colliding
bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

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

// Sets the visibility of the bounding objects
void MyBoundingObjectClass::FlipVisibility()
{
	if (m_bIsVisible == true)
	{
		m_bIsVisible = false;
	}
	else if (m_bIsVisible == false)
	{
		m_bIsVisible = true;
	}
}

void MyBoundingObjectClass::SetVisibility(bool bvis)
{
	m_bIsVisible = bvis;
}

// Gets the color of the bounding object
vector3 MyBoundingObjectClass::GetColor(void)
{
	return m_v3Color;
}

// Sets the color of the bounding object
void MyBoundingObjectClass::SetColor(vector3 a_v3Color)
{
	m_v3Color = a_v3Color;
}

// Renders the bounding object
void MyBoundingObjectClass::Render(void)
{
	if (m_bIsVisible)
	{
		meshManager->AddCubeToRenderList(GetGlobalCenterMatrix() * glm::scale(vector3(GetSize())), m_v3Color, WIRE);
		SetChangingCubeSize();
		meshManager->AddCubeToRenderList(glm::translate(GetGlobalCenter()) * glm::scale(vector3(GetChangingSize())), m_v3Color, WIRE);
		meshManager->AddSphereToRenderList(glm::translate(GetGlobalCenter()) * glm::scale(vector3(m_fRadius * 2)), m_v3Color, WIRE);
	}
}