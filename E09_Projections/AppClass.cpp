#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E09_Projections"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}
void AppClass::InitVariables(void)
{
	jtCamera = jtCamera->Instance();

	m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");

	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper", false, glm::translate(0.0f, 0.0f, -3.0f) * glm::scale(vector3(2.0f)));

	//Init the Bounding Object Manager and pass in the Mesh Manager 
	m_pBOMngr = BoundingObjectMngr::Instance();
	m_pBOMngr->InitMeshManager(m_pMeshMngr);

	//Add Bounding Objects to the models
	//**Must use the same names as when you load the models**
	m_pBOMngr->AddBoundingObject("Steve");
	m_pBOMngr->AddBoundingObject("Creeper");

	//Set the visibility of the creeper's bounding box **used as a test for the method**
	m_pBOMngr->SetBOVisibility("Creeper", true);

	jtCamera->SetUp(vector3(0, 1, 0));
	jtCamera->SetPosition(vector3(0.0f, 0.0f, 14.0f));
	jtCamera->SetTarget(vector3(0.0f, 0.0f, 0.0f));
	jtCamera->SetUp(vector3(0.0f, 1.0f, 0.0f));
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");

	//set the matricies of the BO's 
	m_pBOMngr->SetBOMatrix("Steve", m_pMeshMngr->GetModelMatrix("Steve"));
	m_pBOMngr->SetBOMatrix("Creeper", m_pMeshMngr->GetModelMatrix("Creeper"));

	//Check the Collisions of all of the Bounding Objects
	m_pBOMngr->CheckCollisions();

	//Render Bounding Objects
	// **Like with the Mesh Manager, use the keyword "ALL" to render all stored BO's,
	// or use the name of a model to only render that one.**
	m_pBOMngr->RenderBoundingObjects("ALL");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	jtCamera->MoveForward(0.1f);

	m_pCamera->SetView(jtCamera->GetView());
	m_pCamera->SetProjection(jtCamera->GetProjection(0));
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
