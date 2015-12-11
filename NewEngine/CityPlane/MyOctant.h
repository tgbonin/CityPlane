/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __MYOCTANT_H_
#define __MYOCTANT_H_

#include "RE\ReEng.h"

//System Class
class MyOctant
{
	MyOctant* m_pParent = nullptr;
	MyOctant* m_pChild[8];

	int divisionLevel;
	int maxDivisionLevel;

	float m_fSize = 0.0f; //Radius of the Bounding Object

	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton

	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Object Class

public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyOctant(std::vector<vector3> a_lVectorList);
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyOctant(void);

	MyOctant(MyOctant const& other);

	MyOctant& operator=(MyOctant const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyOctant(void);

	void Swap(MyOctant& other);

	float GetSize(void);

	void DisplayBox(vector3 a_v3Color = REDEFAULT);

	void Subdivide(void);

	void checkObjectsWithinBox(void);


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