#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
		bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
		bLastEscape = false, bLastW = false, bLastS = false, bLastD = false, bLastA = false,
		bLastQ = false, bLastE = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		jtCamera->ChangePitch(1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		jtCamera->ChangeRoll(1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
	{
		jtCamera->ChangeYaw(1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		jtCamera->MoveForward(0.1f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		jtCamera->MoveForward(-0.1f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		jtCamera->ChangeYaw(1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		jtCamera->ChangeYaw(-1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		jtCamera->MoveVertical(-0.1f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		jtCamera->MoveVertical(0.1f);
	}

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	float a_fSpeed = 0.1f;

	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;

	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);

	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	float fAngleX = 0.0f;
	float fAngleY = 0.0f;

	if (MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += DeltaMouse * a_fSpeed;
	}
	else if (MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= DeltaMouse * a_fSpeed;
	}

	if (MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= DeltaMouse * a_fSpeed;
	}
	else if (MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += DeltaMouse * a_fSpeed;
	}

	//mouse control for pitch and roll (airplane)
	jtCamera->ChangePitch(fAngleX);
	jtCamera->ChangeRoll(-fAngleY);
}
