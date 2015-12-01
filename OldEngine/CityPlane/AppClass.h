/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
//include our bounding box stuff
#include "MyBoundingBoxClass.h"
#include "BoundingObject.h"
#include "BoundingObjectMngr.h"
#include "MyBoundingSphereClass.h"
//#include <chrono>
#include "Player.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
public:
	typedef ReEngAppClass super;
	BoundingObjectMngr* m_pBOMngr = nullptr;

	BoundingObject* m_pBO1 = nullptr;
	BoundingObject* m_pBO2 = nullptr;

	MyBoundingSphereClass* m_pBS1 = nullptr;
	MyBoundingSphereClass* m_pBS2 = nullptr;

	vector3 m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	vector3 m_v3O2 = vector3(2.5f, 0.0f, 0.0f);
	vector3 m_v3O3 = vector3(1.0f, 1.0f, 0.0f);

	std::vector<vector3> buildings;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) : super(hInstance, lpCmdLine, nCmdShow) {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName);

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void);

	/*
	Update
	Updates the scene
	*/
	virtual void Update(void);

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void);

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void);

	virtual void ProcessMouse(void);

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void Release(void);

	Player* m_pPlayer;
};

#endif //__APPLICATION_H_
