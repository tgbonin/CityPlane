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
	m_pCameraMngr->SetPositionTargetAndView(vector3(-150.0f, 30.0f, 150.0f), vector3(0.0f), REAXISY);

	m_pPlayer = m_pPlayer->Instance();

	m_pEntityMngr = MyEntityManager::GetInstance();

	gamepad = new Gamepad(1);


	m_pPlayer->SetUp(vector3(0, 1, 0));
	m_pPlayer->SetPosition(vector3(0.0f, 30.0f, 50.0f));
	m_pPlayer->SetTarget(vector3(0.0f, 0.0f, 1.0f));
	m_pPlayer->SetUp(vector3(0.0f, 1.0f, 0.0f));

	std::vector<int> buildingLayout = {
		2, 1, 2, 0, 0, 2,
		0, 1, 2, 1, 0, 1,
		1, 0, 2, 0, 2, 0,
		0, 0, 0, 1, 1, 2,
		2, 2, 1, 1, 0, 1
	};

	
	for(int i = 0; i < buildingLayout.size() - 1; i++){
		String name = "TestBuilding" + std::to_string(i);

		int row = (i / 6);
		int col = (i % 6);
		float separation = 40.0;
		vector3 pos(-150.0f + (separation * row), 0.0f, -150.0f + (separation * col));

		switch (buildingLayout[i])
		{
			case 0: 
				name = "target" + std::to_string(i);
				m_pMeshMngr->LoadModel("\\target.obj", name);

				pos.y = rand() % 30 + 10;
				targets.push_back(pos);

				m_pEntityMngr->AddEntity(name, INT_MAX);
				m_pEntityMngr->SetPosition(pos, name);
				m_pEntityMngr->SetGravityAffected(false, name);

				break;
			case 1:
				m_pMeshMngr->LoadModel("Buildings\\building1.obj", name);

				m_pEntityMngr->AddEntity(name, INT_MAX);
				m_pEntityMngr->SetPosition(pos, name);
				m_pEntityMngr->SetGravityAffected(false, name);

					break;
			case 2:
				m_pMeshMngr->LoadModel("Buildings\\building2.obj", name);

				m_pEntityMngr->AddEntity(name, INT_MAX);
				m_pEntityMngr->SetPosition(pos, name);
				m_pEntityMngr->SetGravityAffected(false, name);

					break;
		}
	}

	m_pMeshMngr->LoadModel("\\biplane.obj", "PLAYER", false);

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

		m_pPlayer->Update();

		m_pEntityMngr->Update();
		m_pEntityMngr->SetPosition(m_pPlayer->position, "PLAYER");
		m_pEntityMngr->SetModelMatrix(m_pPlayer->GetMatrix(), "PLAYER");


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

	m_pMeshMngr->AddPlaneToQueue(matrix4(1.0f) * glm::scale(vector3(500.0f, 1.0f, 500.0f)) * glm::rotate(90.0f, REAXISX), vector3(0.0f, (153.0f / 255.0f), 0.0f));

	m_pEntityMngr->Display(ER_MESH); //Display all objects in Entity manager
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	m_pEntityMngr->ReleaseInstance();
	super::Release(); //release the memory of the inherited fields
}