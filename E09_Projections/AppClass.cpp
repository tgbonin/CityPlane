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

	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper", false, glm::translate(-10.0f, 0.0f, -3.0f) * glm::scale(vector3(2.0f)));
	
	m_pMeshMngr->LoadModel("Buildings\\building1.obj", "TestBuilding1", false, glm::translate(50.0f, 0.0f, -50.0f));
	m_pMeshMngr->LoadModel("Buildings\\building2.obj", "TestBuilding2", false, glm::translate(30.0f, 0.0f, -20.0f));

	buildings.push_back(vector3(50.0f, 0.0f, -50.0f));
	buildings.push_back(vector3(30.0f, 0.0f, -20.0f));

	//Init the Bounding Object Manager and pass in the Mesh Manager 
	m_pBOMngr = BoundingObjectMngr::Instance();
	m_pBOMngr->InitMeshManager(m_pMeshMngr);

	//Add Bounding Objects to the models
	//**Must use the same names as when you load the models**
	m_pBOMngr->AddBoundingObject("Steve");
	m_pBOMngr->AddBoundingObject("Creeper");
	m_pBOMngr->AddBoundingObject("TestBuilding1");
	m_pBOMngr->AddBoundingObject("TestBuilding2");

	// new Bounding Spheres
	m_pBS1 = new MyBoundingSphereClass(m_pMeshMngr->GetVertices("Steve"));
	m_pBS2 = new MyBoundingSphereClass(m_pMeshMngr->GetVertices("Creeper"));

	//Set the visibility of the creeper's bounding box **used as a test for the method**
	m_pBOMngr->SetBOVisibility("Creeper", true);

	jtCamera->SetUp(vector3(0, 1, 0));
	jtCamera->SetPosition(vector3(0.0f, 50.0f, 30.0f));
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

	// SPHERES
	m_pBS1->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"));
	m_pBS2->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Creeper"));

	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3b01), "TestBuilding1");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3b02), "TestBuilding2");

	//set the matricies of the BO's 
	m_pBOMngr->SetBOMatrix("Steve", m_pMeshMngr->GetModelMatrix("Steve"));
	m_pBOMngr->SetBOMatrix("Creeper", m_pMeshMngr->GetModelMatrix("Creeper"));

	m_pBOMngr->SetBOMatrix("TestBuilding1", m_pMeshMngr->GetModelMatrix("TestBuilding1"));
	m_pBOMngr->SetBOMatrix("TestBuilding2", m_pMeshMngr->GetModelMatrix("TestBuilding2"));

	//Check the Collisions of all of the Bounding Objects
	m_pBOMngr->CheckCollisions();

	//Add a representation of the Spheres to the render list
	vector3 v3Color = REWHITE;
	if (m_pBS1->IsColliding(m_pBS2))
		v3Color = RERED;

	m_pMeshMngr->AddSphereToQueue(glm::translate(matrix4(IDENTITY), m_pBS1->GetCenter()) * glm::scale(vector3(m_pBS1->GetRadius()) * 2.0f), v3Color, WIRE);
	m_pMeshMngr->AddSphereToQueue(glm::translate(matrix4(IDENTITY), m_pBS2->GetCenter()) * glm::scale(vector3(m_pBS2->GetRadius()) * 2.0f), v3Color, WIRE);

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
