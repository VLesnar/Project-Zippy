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
	vector<vector3> m_bList;	// Holds a list of the axis-aligned bounding box points
	vector3 m_v3ChangingSize;	// The size of the axis-aligned bounding box
	vector3 m_v3ChangingMin;	// The minimum of the axis-aligned bounding box
	vector3 m_v3ChangingMax;	// The maximum of the axis-aligned bounding box
	matrix4 m_m4ToWorld;	// Matrix that changes coordinates from local to world space
	void Init(void);	// Allocates member fields
	void Release(void);	// Deallocates member fields
	bool m_bIsVisible;	// If the bounding box is visible
	vector3 m_v3Color;	// Holds the color of the bounding object
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();	// The mesh singleton to render bounding objects
	string name; //name of the object used to specify in Manager
public:
	void Swap(MyBoundingObjectClass& other);	// Changes the object's contents with another
	MyBoundingObjectClass(vector<vector3> a_lVectorList, string iname);	// Constructor
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
	void SetVisibility(void);	// Sets the visibility of the bounding object
	vector3 GetColor(void);	// Gets the color of the bounding object
	void SetColor(vector3 a_v3Color);	// Sets the color of the bounding object
	void Render(void);	// Renders the bounding object
	string GetName() { return name; }
};
#endif // __MYBOUNDINGOBJECTCLASS_H_