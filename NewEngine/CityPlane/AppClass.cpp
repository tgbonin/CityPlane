#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Plane City Target Thing"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(REAXISZ * 30.0f, ZERO_V3, REAXISY);

	m_pPlayer = m_pPlayer->Instance();

	m_pMeshMngr->LoadModel("Buildings\\building1.obj", "TestBuilding1");
	m_pMeshMngr->LoadModel("Buildings\\building2.obj", "TestBuilding2");

	m_pMeshMngr->LoadModel("\\biplane.obj", "PLAYER", false);

	buildings.push_back(vector3(50.0f, 0.0f, -50.0f));
	buildings.push_back(vector3(30.0f, 0.0f, -20.0f));


	m_pEntityMngr = MyEntityManager::GetInstance();

	gamepad = new Gamepad(1);


	m_pPlayer->SetUp(vector3(0, 1, 0));
	m_pPlayer->SetPosition(vector3(0.0f, 30.0f, 50.0f));
	m_pPlayer->SetTarget(vector3(0.0f, 0.0f, 1.0f));
	m_pPlayer->SetUp(vector3(0.0f, 1.0f, 0.0f));

	m_pEntityMngr->AddEntity("TestBuilding1", INT_MAX);
	m_pEntityMngr->SetPosition(buildings[0], "TestBuilding1");
	m_pEntityMngr->SetGravityAffected(false, "TestBuilding1");

	m_pEntityMngr->AddEntity("TestBuilding2", INT_MAX);
	m_pEntityMngr->SetPosition(buildings[1], "TestBuilding2");
	m_pEntityMngr->SetGravityAffected(false, "TestBuilding2");

	m_pEntityMngr->AddEntity("PLAYER", 100.0f);
	m_pEntityMngr->SetPosition(m_pPlayer->position, "PLAYER");
	m_pEntityMngr->SetGravityAffected(false, "PLAYER");


	float CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	float CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;
	SetCursorPos(CenterX, CenterY);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//update the player
	m_pPlayer->Update();	

	//First person camera movement
	//if (m_bFPC == true)
	//	CameraRotation();

	gamepad->Update();
	
	m_pEntityMngr->Update();
	m_pEntityMngr->SetPosition(m_pPlayer->position, "PLAYER");
	m_pEntityMngr->SetModelMatrix(m_pPlayer->GetMatrix(), "PLAYER");

	//update the follow camera
	m_pCameraMngr->SetPositionTargetAndView(
		(m_pPlayer->position - ((m_pPlayer->forward * 10.0f) + (-m_pPlayer->up * 3.0f))),
		m_pPlayer->position,
		m_pPlayer->up
	);

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	m_pEntityMngr->Display(ER_MESH | ER_OB); //Display all objects in Entity manager
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	m_pEntityMngr->ReleaseInstance();
	super::Release(); //release the memory of the inherited fields
}