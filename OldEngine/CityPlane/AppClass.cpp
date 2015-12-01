#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("City Plane Thing"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}
void AppClass::InitVariables(void)
{
	m_pPlayer = m_pPlayer->Instance();
	
	m_pMeshMngr->LoadModel("Buildings\\building1.obj", "TestBuilding1");
	m_pMeshMngr->LoadModel("Buildings\\building2.obj", "TestBuilding2");

	m_pMeshMngr->LoadModel("\\biplane.obj", "Biplane", false);

	buildings.push_back(vector3(50.0f, 0.0f, -50.0f));
	buildings.push_back(vector3(30.0f, 0.0f, -20.0f));

	//Init the Bounding Object Manager and pass in the Mesh Manager 
	m_pBOMngr = BoundingObjectMngr::Instance();
	m_pBOMngr->InitMeshManager(m_pMeshMngr);

	//Add Bounding Objects to the models
	//**Must use the same names as when you load the models**
	m_pBOMngr->AddBoundingObject("TestBuilding1");
	m_pBOMngr->AddBoundingObject("TestBuilding2");
	m_pBOMngr->AddBoundingObject("Biplane");


	//setup the player object
	m_pPlayer->SetUp(vector3(0, 1, 0));
	m_pPlayer->SetPosition(vector3(0.0f, 30.0f, 50.0f));
	m_pPlayer->SetTarget(vector3(0.0f, 0.0f, 1.0f));
	m_pPlayer->SetUp(vector3(0.0f, 1.0f, 0.0f));

}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	m_pPlayer->Update();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	// SPHERES
	m_pMeshMngr->SetModelMatrix(glm::translate(buildings[0]), "TestBuilding1");
	m_pMeshMngr->SetModelMatrix(glm::translate(buildings[1]), "TestBuilding2");
	m_pMeshMngr->SetModelMatrix(m_pPlayer->GetMatrix(), "Biplane");

	//set the matricies of the BO's 
	m_pBOMngr->SetBOMatrix("TestBuilding1", m_pMeshMngr->GetModelMatrix("TestBuilding1"));
	m_pBOMngr->SetBOMatrix("TestBuilding2", m_pMeshMngr->GetModelMatrix("TestBuilding2"));
	m_pBOMngr->SetBOMatrix("Biplane", m_pMeshMngr->GetModelMatrix("Biplane"));

	//Check the Collisions of all of the Bounding Objects
	m_pBOMngr->CheckCollisions();

	//Render Bounding Objects
	// **Like with the Mesh Manager, use the keyword "ALL" to render all stored BO's,
	// or use the name of a model to only render that one.**
	m_pBOMngr->RenderBoundingObjects("ALL");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	m_pCamera->SetView(m_pPlayer->GetView());
	m_pCamera->SetProjection(m_pPlayer->GetProjection(0));
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	m_pGrid->Render(); //renders the XY grid with a 100% scale

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}
