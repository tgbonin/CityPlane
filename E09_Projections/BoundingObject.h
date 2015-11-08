#ifndef __BOUNDINGOBJECT_H_
#define __BOUNDINGOBJECT_H_

#include "RE/ReEng.h"
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>


class BoundingObject
{
	matrix4 m_m4ToWorld = matrix4(1.0f);		//Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f);		//Will store the center point of the box Class
	vector3 m_v3Min = vector3(0.0f);		//Will store the minimum vector of the box Class
	vector3 m_v3Max = vector3(0.0f);		//Will store the maximum vector of the box Class

	vector3 m_v3CenterG = vector3(0.0f);	//Will store the center point of the box Class
	vector3 m_v3MinG = vector3(0.0f);		//Will store the minimum vector of the box Class
	vector3 m_v3MaxG = vector3(0.0f);		//Will store the maximum vector of the box Class

	vector3 m_v3HalfWidth = vector3(0.0f);	//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);	//Will store half the size of all sides
	float m_fRadius = 0.0f;

	bool m_bIsVisible = true;				//Switches the visibility of the BO
	vector3 m_v3Colour = REWHITE;
	

public:
	
	BoundingObject(std::vector<vector3> a_lVectorList);

	BoundingObject(BoundingObject const& other);

	BoundingObject& operator=(BoundingObject const& other);

	~BoundingObject(void);

	void Swap(BoundingObject& other);

	void SetModelMatrix(matrix4 a_m4ToWorld);

	void SetVisibility(bool a_bVisibility);

	void SetColour(vector3 a_v3Colour);

	matrix4 GetModelMatrix(void);

	vector3 GetCenterLocal(void);

	vector3 GetCenterGlobal(void);

	vector3 GetHalfWidth(void);

	vector3 GetHalfWidthG(void);

	float GetRadiusG(void);

	bool IsColliding(BoundingObject* const a_pOther);

	void DrawBoundingObjects(MeshManagerSingleton*);

private:
	void Release(void);

	void Init(void);
};

#endif