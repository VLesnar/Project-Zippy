/*-----------------------------------------------
Programmers: Alexander Bronner, Joseph Horsmann
	Veronica Lesnar, & Steven Siewert
MyBoundingObjectClass.h - Holds the declarations
for MyBoundingObjectClass.cpp
-----------------------------------------------*/
#ifndef __MYBOUNDINGOBJECTCLASS_H_
#define __MYBOUNDINGOBJECTCLASS_H_

#include "RE/ReEng.h"

using namespace std;

class MyBoundingObjectClass
{
private:
	vector<vector3> m_vList;	// Holds a list of points from the model
	vector3 m_v3Max;	// The maximum vector of the bounding box
	vector3 m_v3Min;	// The minimum vector of the bounding box
	vector3 m_v3Center;	// The center of the model
	float m_fRadius;	// Radius of the bounding sphere
	vector3 m_v3Size;	// The size of the bounding box
	vector3 m_v3ChangingSize;	// The size of the axis-aligned bounding box
	matrix4 m_m4ToWorld;	// Matrix that changes coordinates from local to world space
	void Init(void);	// Allocates member fields
	void Release(void);	// Deallocates member fields
public:
	void Swap(MyBoundingObjectClass& other);	// Changes the object's contents with another
	MyBoundingObjectClass(vector<vector3> a_lVectorList);	// Constructor
	MyBoundingObjectClass(MyBoundingObjectClass const &other);	// Copy Constructor
	MyBoundingObjectClass& operator=(MyBoundingObjectClass const& other);	// Copy Assignment Operator
	MyBoundingObjectClass(void);	// Destructor
	vector3 GetGlobalCenter(void);	// Gets the center in global coordinates
	matrix4 GetGlobalCenterMatrix(void);	// Gets the matrix of the center in global coordinates
	float GetRadius(void);	// Gets the object's radius
	vector3 GetSize(void);	// Gets the object's bounding box's size
	vector3 GetChangingSize(void);	// Gets the object's axis-aligned bounding box's size
	void SetChangingCubeSize(void);	// Changes the size of the axis-aligned bounding box
	matrix4 GetModelMatrix(void);	// Gets the object's matrix
	void SetModelMatrix(matrix4 a_m4ToWorld);	// Sets the object's matrix
	bool IsColliding(MyBoundingObjectClass* const a_pOther);	// Checks to see if two objects are colliding
};
#endif // __MYBOUNDINGOBJECTCLASS_H_