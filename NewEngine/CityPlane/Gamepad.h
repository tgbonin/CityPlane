#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Windows.h>
#include <Xinput.h>


class Gamepad
{
public:
	// Function prototypes
	//---------------------//

	// Constructors
	Gamepad();
	Gamepad(int a_iIndex);

	void Update(); // Update gamepad state

	// Thumbstick functions
	// - Return true if stick is inside deadzone, false if outside
	bool LStick_InDeadzone();
	bool RStick_InDeadzone();

	float LeftStick_X();  // Return X axis of left stick
	float LeftStick_Y();  // Return Y axis of left stick
	float RightStick_X(); // Return X axis of right stick
	float RightStick_Y(); // Return Y axis of right stick

	// Utility functions
	XINPUT_STATE GetState(); // Return gamepad state
	int GetIndex();          // Return gamepad index
	bool Connected();        // Return true if gamepad is connected

private:
	// Member variables
	//---------------------//

	XINPUT_STATE m_State; // Current gamepad state
	int m_iGamepadIndex;  // Gamepad index (eg. 1,2,3,4)
};

#endif // GAMEPAD_H