#pragma once

#include "RE/ReEng.h"
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "BoundingObject.h"

class BoundingObjectMngr
{
	/*
		The std::map is similar to a c# dictionary in that it takes in 
		a key and a value to store with it. In this case I used a string
		for the objects name as the key which is combined with a Bounding
		Object.
	*/
	std::map<std::string, BoundingObject*> m_mapBoundingObjectMap;

	//Vector containing all instances of Bounding Objects
	std::vector<BoundingObject*> m_lBOList;

public:
	static BoundingObjectMngr* Instance();

	uint m_nObjectCount = 0; //number of AABB in the list
	static BoundingObjectMngr* m_pInstance; // Singleton pointer
	std::vector<BoundingObject*> m_lObject; //list of AABB
	MeshManagerSingleton* m_pMeshMngr;//Mesh Manager Singleton
	std::vector<std::vector<int>> m_llCollidingIndices; //List of list of colliding indices.
	std::map<String, uint> m_mapIndex;//Map relating the mesh and the index


	/*
		InitMeshManager
		Initializes m_pMeshMngr with the pointer from AppClass for use with 
		certain functions
	*/
	void InitMeshManager(MeshManagerSingleton* a_pMeshMngr);

	/*
		SetBOVisibility
		Sets the visibility of a Bounding Object
	*/
	void SetBOVisibility(std::string a_sObjectName, bool a_bVisibility);

	/*
		SetBOColour
		Sets the colour of a Bounding Object
	*/
	void SetBOColour(std::string a_sObjectName, vector3 a_v3Colour);

	/*
		SetBOMatrix
		Sets the model matrix of the specified Bounding Object
	*/
	void SetBOMatrix(std::string a_sObjectName, matrix4 a_m4ToWorld);

	/*
		GetNumberBoundingObjects
		Returns the number of Bounding Objects currently saved in the list
	*/
	int GetNumberBoundingObjects(void);

	/*
		AddBoundingObject
		Adds a bounding object to the map/list
	*/
	void AddBoundingObject(std::string a_sObjectName);

	/*
		RenderBoundingObjects
		Renders a specific or all bounding objects stored
	*/
	void RenderBoundingObjects(std::string a_sObjectName);

	/*
		CheckCollisions
		Checks the collisions of boudning objects against each other 
		and sets their colour depending on whether there is one detected
	*/
	void CheckCollisions(void);

	void DisplaySphere(int a_nIndex, vector3 a_v3Color);

	void DisplayOriented(int a_nIndex, vector3 a_v3Color);

	void DisplayReAlligned(String a_sName, vector3 a_v3Color);

	void DisplayReAlligned(int a_nIndex, vector3 a_v3Color);

	void Update(void);

	std::vector<int> GetCollidingVector(String a_sIndex);

	std::vector<int> GetCollidingVector(uint a_nIndex);

	int GetIndex(String a_sIndex);

private:
	BoundingObjectMngr(){};
	BoundingObjectMngr(BoundingObjectMngr const&);
	BoundingObjectMngr& operator=(BoundingObjectMngr const&){};
};

