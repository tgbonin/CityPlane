/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __MYOCTANT_H_
#define __MYOCTANT_H_

#include "RE\ReEng.h"
#include "MyBOManager.h"

//System Class
class MyOctant
{
	static uint m_nMaxSubLevel;
	uint m_nLevel = 0;
	uint m_nChildren = 0;
	MyOctant* m_pParent = nullptr;
	MyOctant* m_pChild[8];
	std::vector<int> m_vecContainedObjects;

	float m_fSize = 0.0f; //Size of the octant

	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton
	MyBOManager* m_pBOMngr = nullptr;

	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Object Class
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyOctant(vector3 a_v3Center, float a_fSize);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyOctant(MyOctant const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyOctant& operator=(MyOctant const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyOctant(void);
	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- MyOctant& other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(MyOctant& other);
	
	/*
	USAGE: Gets the Octant size
	ARGUMENTS: ---
	OUTPUT: Size of the octant
	*/
	float GetSize(void);
	
	/*
	USAGE:
	ARGUMENTS:
	- vector3 a_v3Color = REDEFAULT -> Color of the Object to display if the value is REDEFAULT it
	-- will display Objects in white and colliding ones in red.
	OUTPUT: ---
	*/
	void Display();
	void Subdivide(void);
	MyOctant* GetChild(uint nIndex);
	void KillBranch(void);
	void OcTreeCollisions(void);

private:
	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

#endif //__MYOCTANT_H__
