/*-----------------------------------------------
Programmers: Alexander Bronner, Joseph Horsmann
	Veronica Lesnar, & Steven Siewert
MyBoundingObjectClass.h - Contains methods to
	create sphere and box colliders
-----------------------------------------------*/
#include "MyBoundingObjectClass.h"

// Allocates member fields
void MyBoundingObjectClass::Init() {
	m_vList = vector<vector3>();
	m_v3Max = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Center = vector3(0.0f);
	m_fRadius = 0.0f;
	m_v3Size = vector3(0.0f);
	m_bList = vector<vector3>();
	m_v3ChangingSize = vector3(0.0f);
	m_v3ChangingMin = vector3(0.0f);
	m_v3ChangingMax = vector3(0.0f);
	m_m4ToWorld = IDENTITY_M4;
	m_bIsVisible = true;
	meshManager->GetInstance();
}

// Changes the object's contents with another
void MyBoundingObjectClass::Swap(MyBoundingObjectClass& other) {
	swap(m_vList, other.m_vList);
	swap(m_v3Max, other.m_v3Max);
	swap(m_v3Min, other.m_v3Min);
	swap(m_v3Center, other.m_v3Center);
	swap(m_fRadius, other.m_fRadius);
	swap(m_v3Size, other.m_v3Size);
	swap(m_bList, other.m_bList);
	swap(m_v3ChangingSize, other.m_v3ChangingSize);
	swap(m_v3ChangingMin, other.m_v3ChangingMin);
	swap(m_v3ChangingMax, other.m_v3ChangingMax);
	swap(m_m4ToWorld, other.m_m4ToWorld);
}

// Deallocates member fields
void MyBoundingObjectClass::Release() {

}

// Constructor
MyBoundingObjectClass::MyBoundingObjectClass(vector<vector3> a_lVectorList) {
	// Store the list of vertices from the model
	m_vList = a_lVectorList;

	// Calculate the max, min, center, radius, and size
	uint nVertexCount = m_vList.size();

	// Checks to make sure there are vertices stored
	if (nVertexCount > 0) {
		m_v3Max = m_vList[0];
		m_v3Min = m_vList[0];
	}

	// Set the max and the min vectors
	for (uint i = 0; i < nVertexCount; i++) {
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
MyBoundingObjectClass::MyBoundingObjectClass(MyBoundingObjectClass const& other) {
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
MyBoundingObjectClass& MyBoundingObjectClass::operator=(MyBoundingObjectClass const& other) {
	if (this != &other) {
		Release();
		Init();
		MyBoundingObjectClass temp(other);
		Swap(temp);
	}

	return *this;
}

// Destructor
MyBoundingObjectClass::MyBoundingObjectClass() {
	Release();
}

// Gets the center in global coordinates
vector3 MyBoundingObjectClass::GetGlobalCenter() {
	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));
}

// Gets the matrix of the center in global coordinates
matrix4 MyBoundingObjectClass::GetGlobalCenterMatrix(void) {
	return glm::translate(m_m4ToWorld, m_v3Center);
}

// Gets the object's radius
float MyBoundingObjectClass::GetRadius() {
	return m_fRadius;
}

// Gets the object's bounding box's size
vector3 MyBoundingObjectClass::GetSize() {
	return m_v3Size;
}

// Gets the object's axis-aligned bounding box's size
vector3 MyBoundingObjectClass::GetChangingSize() {
	return m_v3ChangingSize;
}

// Changes the size of the axis-aligned bounding box
void MyBoundingObjectClass::SetChangingCubeSize() {
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
matrix4 MyBoundingObjectClass::GetModelMatrix() {
	return m_m4ToWorld;
}

// Sets the object's matrix
void MyBoundingObjectClass::SetModelMatrix(matrix4 a_m4ToWorld) {
	m_m4ToWorld = a_m4ToWorld * glm::translate(m_v3Center);
}

// Checks to see if two objects are colliding
bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass* const a_pOther) {
	// Get the centers for collision check
	vector3 v3Temp1 = this->GetGlobalCenter();	// First object
	vector3 v3Temp2 = a_pOther->GetGlobalCenter();	// Second object

	bool bAreColliding = true;	// If the two objects are colliding

	// Sphere collision detection
	// Two spheres have collided
	if (glm::distance(v3Temp1, v3Temp2) < (this->m_fRadius + a_pOther->GetRadius())) {
		// Box collision detection
		vector3 vMin1 = v3Temp1 + m_v3ChangingMin;
		vector3 vMax1 = v3Temp1 + m_v3ChangingMax;
		vector3 vMin2 = v3Temp2 + a_pOther->m_v3ChangingMin;
		vector3 vMax2 = v3Temp2 + a_pOther->m_v3ChangingMax;

		//Check for X
		if (vMax1.x < vMin2.x)
			bAreColliding = false;
		if (vMin1.x > vMax2.x)
			bAreColliding = false;

		//Check for Y
		if (vMax1.y < vMin2.y)
			bAreColliding = false;
		if (vMin1.y > vMax2.y)
			bAreColliding = false;

		//Check for Z
		if (vMax1.z < vMin2.z)
			bAreColliding = false;
		if (vMin1.z > vMax2.z)
			bAreColliding = false;
	}
	// No sphere collision
	else {
		bAreColliding = false;
	}

	return bAreColliding;
}

// Sets the visibility of the bounding objects
void MyBoundingObjectClass::SetVisibility() {
	if (m_bIsVisible == true) {
		m_bIsVisible = false;
	}
	else if (m_bIsVisible == false) {
		m_bIsVisible = true;
	}
}

// Gets the color of the bounding object
vector3 MyBoundingObjectClass::GetColor(void) {
	return m_v3Color;
}

// Sets the color of the bounding object
void MyBoundingObjectClass::SetColor(vector3 a_v3Color) {
	m_v3Color = a_v3Color;
}

// Renders the bounding object
void MyBoundingObjectClass::Render(void) {
	if (m_bIsVisible) {
		meshManager->AddSphereToQueue(m_m4ToWorld, m_v3Color, WIRE);
		meshManager->AddCubeToQueue(m_m4ToWorld, m_v3Color, WIRE);
	}
}