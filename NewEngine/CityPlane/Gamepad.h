#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Windows.h>
#include <Xinput.h>

// XInput Button values
static const WORD XINPUT_Buttons[] = {
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

// XInput Button IDs
struct XButtonIDs
{
	// Function prototypes
	//---------------------//

	XButtonIDs(); // Default constructor

	// Member variables
	//---------------------//

	int A, B, X, Y; // 'Action' buttons

	// Directional Pad (D-Pad)
	int DPad_Up, DPad_Down, DPad_Left, DPad_Right;

	// Shoulder ('Bumper') buttons
	int L_Shoulder, R_Shoulder;

	// Thumbstick buttons
	int L_Thumbstick, R_Thumbstick;

	int Start; // 'START' button
	int Back;  // 'BACK' button
};

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
	bool GetButtonPressed(int a_iButton);

private:
	// Member variables
	//---------------------//

	XINPUT_STATE m_State; // Current gamepad state
	int m_iGamepadIndex;  // Gamepad index (eg. 1,2,3,4)
};

#endif // GAMEPAD_H

// Externally define the XButtonIDs struct as XButtons
extern XButtonIDs XButtons;