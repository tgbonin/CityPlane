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
	m_pMeshMngr->LoadModel("Buildings\\building1.obj", "TestBuilding3");
	m_pMeshMngr->LoadModel("Buildings\\building2.obj", "TestBuilding4");
	m_pMeshMngr->LoadModel("Buildings\\building1.obj", "TestBuilding5");
	m_pMeshMngr->LoadModel("Buildings\\building2.obj", "TestBuilding6");
	m_pMeshMngr->LoadModel("Buildings\\building1.obj", "TestBuilding7");
	m_pMeshMngr->LoadModel("Buildings\\building2.obj", "TestBuilding8");

	m_pMeshMngr->LoadModel("\\biplane.obj", "PLAYER", false);

	buildings.push_back(vector3(50.0f, 0.0f, -50.0f));
	buildings.push_back(vector3(30.0f, 0.0f, -20.0f));

	buildings.push_back(vector3(100.0f, 0.0f, -50.0f));
	buildings.push_back(vector3(80.0f, 0.0f, -20.0f));

	buildings.push_back(vector3(0.0f, 0.0f, -50.0f));
	buildings.push_back(vector3(30.0f, 0.0f, -700.0f));

	buildings.push_back(vector3(-500.0f, 0.0f, -100.0f));
	buildings.push_back(vector3(0.0f, 0.0f, 80.0f));


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

	m_pEntityMngr->AddEntity("TestBuilding3", INT_MAX);
	m_pEntityMngr->SetPosition(buildings[2], "TestBuilding3");
	m_pEntityMngr->SetGravityAffected(false, "TestBuilding3");

	m_pEntityMngr->AddEntity("TestBuilding4", INT_MAX);
	m_pEntityMngr->SetPosition(buildings[3], "TestBuilding4");
	m_pEntityMngr->SetGravityAffected(false, "TestBuilding4");

	m_pEntityMngr->AddEntity("TestBuilding5", INT_MAX);
	m_pEntityMngr->SetPosition(buildings[4], "TestBuilding5");
	m_pEntityMngr->SetGravityAffected(false, "TestBuilding5");

	m_pEntityMngr->AddEntity("TestBuilding6", INT_MAX);
	m_pEntityMngr->SetPosition(buildings[5], "TestBuilding6");
	m_pEntityMngr->SetGravityAffected(false, "TestBuilding6");

	m_pEntityMngr->AddEntity("TestBuilding7", INT_MAX);
	m_pEntityMngr->SetPosition(buildings[6], "TestBuilding7");
	m_pEntityMngr->SetGravityAffected(false, "TestBuilding7");

	m_pEntityMngr->AddEntity("TestBuilding8", INT_MAX);
	m_pEntityMngr->SetPosition(buildings[7], "TestBuilding8");
	m_pEntityMngr->SetGravityAffected(false, "TestBuilding8");


	m_pEntityMngr->AddEntity("PLAYER", 100.0f);
	m_pEntityMngr->SetPosition(m_pPlayer->position, "PLAYER");
	m_pEntityMngr->SetGravityAffected(false, "PLAYER");


	float CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	float CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;
	SetCursorPos(CenterX, CenterY);

	state = GAME_START;
	clockIndex = m_pSystem->AddClock();
}

void AppClass::Update(void)
{


	if (state == GAME_START){
		m_pMeshMngr->Print("Press 'Enter' Or 'Space' To Start The Game");
	}
	else if (state == GAME_PLAY){
		gamepad->Update();
		if (m_pPlayer->position.y < 0){
			state = GAME_OVER;
			return;
		}
		
		//Update the system's time
		m_pSystem->UpdateTime();

		//Update the mesh manager's time without updating for collision detection
		m_pMeshMngr->Update(false);

		//First person camera movement
		//if (m_bFPC == true)
		//	CameraRotation();

		m_pEntityMngr->Update();
		m_pEntityMngr->SetPosition(m_pPlayer->position, "PLAYER");
		m_pEntityMngr->SetModelMatrix(m_pPlayer->GetMatrix(), "PLAYER");

		m_pMeshMngr->AddPlaneToQueue(matrix4(1.0f) * glm::scale(vector3(500.0f, 1.0f, 500.0f)) * glm::rotate(90.0f, REAXISX), vector3(0.0f, (153.0f / 255.0f), 0.0f));

		float cameraDamp = 0.1f;
		vector3 curPos = m_pCameraMngr->GetPosition();
		vector3 wantPos = m_pPlayer->position - ((m_pPlayer->forward * 15.0f) + (-m_pPlayer->up * 3.0f));
		vector3 diff = wantPos - curPos;

		vector3 posFinal = curPos + (diff * cameraDamp);

		//update the follow camera
		m_pCameraMngr->SetPositionTargetAndView(
			posFinal,
			m_pPlayer->position,
			m_pPlayer->up
			);
		timePassed += m_pSystem->LapClock(clockIndex);
		
		//Indicate the FPS
		int nFPS = m_pSystem->GetFPS();
		//print info into the console
		printf("FPS: %d            \r", nFPS);//print the Frames per Second
		//Print info on the screen	
		m_pMeshMngr->Print("FPS:");
		m_pMeshMngr->Print(std::to_string(nFPS), RERED);
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->Print("Time: " + std::to_string((int)timePassed), REWHITE);
		/*std::vector<MyBOClass*> BO = m_pEntityMngr->GetEntity("PLAYER")->m_pColliderManager->m_lObject;
		for (int i = 0; i < BO.size(); i++)
		{
			if (i == BO.size() - 1){
				if (BO[i]->IsColliding(BO[0])){
					state == GAME_OVER;
					return;
				}
			}
			else if (BO[i]->IsColliding(BO[i + 1])){
				state == GAME_OVER;
				return;
			}
		}*/
	}
	else { // state == GAME_OVER
		m_pMeshMngr->Print("You Lost! Your Final Score Was 0");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->Print("Press 'Enter' Or 'Space' To Play Again");
	}
	
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	//switch (m_pCameraMngr->GetCameraMode())
	//{
	//default: //Perspective
	//	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOX:
	//	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOY:
	//	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOZ:
	//	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
	//	break;
	//}

	m_pEntityMngr->Display(ER_MESH); //Display all objects in Entity manager
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	m_pEntityMngr->ReleaseInstance();
	super::Release(); //release the memory of the inherited fields
}