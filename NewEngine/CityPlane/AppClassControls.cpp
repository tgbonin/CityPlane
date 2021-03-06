#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false, bLastReturn = false, bLastSpace = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	//	bModifier = true;
#pragma endregion

#pragma region Game State Buttons
	if ((bLastSpace || bLastReturn) && state == GAME_OVER)
	{
		m_pEntityMngr->DeleteTargets();

		m_pEntityMngr->SetNumTargets(10);

		std::vector<int> buildingLayout = {
			2, 1, 2, 0, 0, 2,
			0, 1, 2, 1, 0, 1,
			1, 0, 2, 0, 2, 0,
			0, 3, 0, 1, 1, 2,
			2, 2, 1, 1, 0, 1
		};


		for (int i = 0; i < buildingLayout.size() - 1; i++){
			String name = "Building" + std::to_string(i);

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
			}
		}


		m_pPlayer->SetPosition(vector3(120.0f, 30.0f, 50.0f));
		m_pPlayer->SetTarget(vector3(0.0f, 30.0f, 1.0f));
		m_pPlayer->SetUp(vector3(0.0f, 1.0f, 0.0f));
		m_pPlayer->MoveVertical(0.0f);

		state = GAME_PLAY;
		m_pEntityMngr->gameOver = false;
		timePassed = 0;
	}
	
	if ((bLastSpace || bLastReturn) && state == GAME_START)
	{
		m_pPlayer->SetPosition(vector3(120.0f, 30.0f, 50.0f));
		m_pPlayer->SetTarget(vector3(0.0f, 30.0f, 1.0f));
		m_pPlayer->SetUp(vector3(0.0f, 1.0f, 0.0f));
		m_pPlayer->MoveVertical(0.0f);

		state = GAME_PLAY;
		m_pEntityMngr->gameOver = false;
	}
#pragma endregion

#pragma region Camera Positioning
	if (!(gamepad->RStick_InDeadzone()))
	{
		m_pPlayer->ChangePitch(1.0f * gamepad->RightStick_Y());
		m_pPlayer->ChangeRoll(-2.0f * gamepad->RightStick_X());
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_pPlayer->ChangePitch(0.5f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_pPlayer->ChangePitch(-0.5f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_pPlayer->ChangeRoll(-1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_pPlayer->ChangeRoll(1.0f);
	}


#pragma region Camera Positioning

	if (state == GAME_PLAY){

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_pPlayer->ChangePitch(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_pPlayer->ChangePitch(-1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_pPlayer->ChangeRoll(-2.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_pPlayer->ChangeRoll(2.0f);
		}



		//boost
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_pPlayer->MoveForward(0.1f);
		}
		if (gamepad->GetButtonPressed(XButtons.A)){
			m_pPlayer->MoveForward(0.1f);
		}

		//slow-down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_pPlayer->MoveForward(-0.05f);
		}
		if (gamepad->GetButtonPressed(XButtons.A)){
			m_pPlayer->MoveForward(-0.05f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_pPlayer->ChangeRoll(-1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_pPlayer->ChangeRoll(1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			m_pPlayer->MoveVertical(-0.1f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			m_pPlayer->MoveVertical(0.1f);
		}

		//Fire
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && currentTime - timeLastFired > 0.2f){
			String s = "BULLET" + std::to_string(currentTime);
			timeLastFired = currentTime;
			m_pEntityMngr->AddEntity("BULLET", "BULLET", 1.0f);
			PlaneBullet* pb = new PlaneBullet(m_pPlayer->position + m_pPlayer->forward*3.0f, m_pPlayer->forward);
			m_bullets.push_back(pb);
			pb->timeFired = timeLastFired;
		}
		if (gamepad->GetButtonPressed(XButtons.R_Shoulder)){
			String s = "BULLET" + std::to_string(currentTime);
			timeLastFired = currentTime;
			m_pEntityMngr->AddEntity("BULLET", "BULLET", 1.0f);
			PlaneBullet* pb = new PlaneBullet(m_pPlayer->position + m_pPlayer->forward*3.0f, m_pPlayer->forward);
			m_bullets.push_back(pb);
			pb->timeFired = timeLastFired;
		}

	}
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));

	bool bEnter = false;
	ON_KEY_PRESS_RELEASE(Return, NULL, bEnter = true);
	if (bEnter)
	{

	}
	bool bSpace = false;
	ON_KEY_PRESS_RELEASE(Space, NULL, bSpace = true);
	if (bSpace)
	{

	}
#pragma endregion

}
void AppClass::ProcessMouse(void)
{
	float a_fSpeed = 0.1f;

	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);

	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	float fAngleX = 0.0f;
	float fAngleY = 0.0f;

	//soften the mouse sensitivity
	float soften = 0.2f;

	if (MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += DeltaMouse * a_fSpeed * soften;
	}
	else if (MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= DeltaMouse * a_fSpeed * soften;
	}

	if (MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= DeltaMouse * a_fSpeed * soften;
	}
	else if (MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += DeltaMouse * a_fSpeed * soften;
	}

	//mouse control for pitch and roll (airplane)
	m_pPlayer->ChangePitch(fAngleX);
	m_pPlayer->ChangeYaw(fAngleY * 0.8);
}
