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

	m_pPlayer->SetPosition(vector3(0.0f, 30.0f, 50.0f));
	m_pPlayer->SetTarget(vector3(0.0f, 0.0f, 1.0f));
	m_pPlayer->SetUp(vector3(0.0f, 1.0f, 0.0f));

	std::vector<int> buildingLayout = {
		2, 1, 2, 0, 0, 2,
		0, 1, 2, 1, 0, 1,
		1, 0, 2, 0, 2, 0,
		0, 3, 0, 1, 1, 2,
		2, 2, 1, 1, 0, 1
	};

	
	for(int i = 0; i < buildingLayout.size() - 1; i++){
		String name = "TestBuilding" + std::to_string(i);

		int row = (i / 6);
		int col = (i % 6);
		float separation = 40.0;
		vector3 pos(-120.0f + (separation * row), 0.0f, -100.0f + (separation * col));

		switch (buildingLayout[i])
		{
			case 0: 
				name = "target" + std::to_string(i);
				m_pMeshMngr->LoadModel("\\target.obj", name);

				pos.y = rand() % 30 + 10;

				m_pEntityMngr->AddEntity(name, "target", (float)INT_MAX);
				m_pEntityMngr->SetPosition(pos, name);
				m_pEntityMngr->SetGravityAffected(false, name);

				break;
			case 1:
				m_pMeshMngr->LoadModel("Buildings\\building1.obj", name);

				m_pEntityMngr->AddEntity(name, "building", (float)INT_MAX);
				m_pEntityMngr->SetPosition(pos, name);
				m_pEntityMngr->SetGravityAffected(false, name);

					break;
			case 2:
				m_pMeshMngr->LoadModel("Buildings\\building2.obj", name);

				m_pEntityMngr->AddEntity(name, "building", (float)INT_MAX);
				m_pEntityMngr->SetPosition(pos, name);
				m_pEntityMngr->SetGravityAffected(false, name);

					break;
		}
	}

	m_pMeshMngr->LoadModel("\\biplane.obj", "PLAYER", false);

	m_pEntityMngr->AddEntity("PLAYER", "player",100.0f);
	m_pEntityMngr->SetPosition(m_pPlayer->position, "PLAYER");
	m_pEntityMngr->SetGravityAffected(false, "PLAYER");


	int CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	int CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;
	SetCursorPos(CenterX, CenterY);

	state = GAME_START;
	clockIndex = m_pSystem->AddClock();
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	if (state == GAME_START){
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("                Press 'Enter' Or 'Space' To Start The Game");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("           Shoot all of the targets to win! Get them all in the");
		m_pMeshMngr->PrintLine("                          lowest time you can!");

		static double fRunTime = 0.0f;
		float duration = 30.0f;
		double fTime = m_pSystem->LapClock();
		fRunTime += fTime;

		if (fRunTime > duration) fRunTime = 0.0f;

		float fPercent = MapValue(static_cast<float>(fRunTime), 0.0f, duration, 0.0f, 1.0f);
		float angle = 360 * fPercent;

		matrix4 cameraPos = glm::rotate(angle, REAXISY) * glm::translate(vector3(150.0f, 30.0f, 0.0f));
		vector3 derp = vector3(cameraPos[3]);
		
		m_pCameraMngr->SetPositionTargetAndView(derp, vector3(0.0f), REAXISY);
	}
	else if (state == GAME_PLAY){
		gamepad->Update();
		if (m_pPlayer->position.y < 0 || m_pEntityMngr->gameOver){
			state = GAME_OVER;
			m_pEntityMngr->gameOver = false;
			return;
		}


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
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->Print("Targets left: " + std::to_string(m_pEntityMngr->GetNumTargets()) , REWHITE);

		if (m_pEntityMngr->GetNumTargets() == 0) state = GAME_OVER;
	}
	else { // state == GAME_OVER
		m_pEntityMngr->gameOver = false;
		m_pMeshMngr->PrintLine("Game Over! Your Final Score Was " + std::to_string(10 - m_pEntityMngr->GetNumTargets()) + " / 10 targets");
		m_pMeshMngr->PrintLine("and you finished in " + std::to_string((int)timePassed) + " seconds!");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->Print("Press 'Escape' to exit the game");
	}
	
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

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