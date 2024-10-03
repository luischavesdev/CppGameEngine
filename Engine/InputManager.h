#pragma once
#include <stdint.h>

class InputManager 
{
public:
	enum MouseButtonEnum { left = 0, right, middle, back, forward };

	enum KeyboardKeysEnum{ W_KEY = 0, A_KEY, S_KEY, D_KEY, UP_KEY, LEFT_KEY, DOWN_KEY, RIGHT_KEY, SPACE_KEY, L_CTRL_KEY, L_SHFT_KEY};

	enum ControllerButtonEnum { DPAD_LEFT = 0, DPAD_RIGHT, DPAD_UP, DPAD_DOWN, BTN_A };

	struct ControllerButtonState
	{
		bool DpadLeft = false;
		bool padRight = false;
		bool DpadUp = false;
		bool DpadDown = false;
		bool BtnA = false;
	};
	

	struct MousePos 
	{
		int MouseXPos;
		int MouseYPos;
	};

private:
	uint8_t* myPreviousKeyboardState;
	const uint8_t* myKeyboardState;
	int myKeyLength;

	int myPreviousMouseState;
	int myMouseState;
	MousePos myMousePosition;
	
	ControllerButtonState myPreviousControllerState;
	ControllerButtonState myControllerState;


public:
	InputManager();

	/*	KEY  MANAGEMENT  */
	bool KeyDown(KeyboardKeysEnum keyPress);
	bool KeyPressed(KeyboardKeysEnum keyPress);
	bool KeyReleased(KeyboardKeysEnum keyPress);

	bool MouseButtonDown(MouseButtonEnum button);
	bool MouseButtonPressed(MouseButtonEnum button);
	bool MouseButtonReleased(MouseButtonEnum button);
	MousePos CurrentMousePosition();

	bool ControllerInputDown(ControllerButtonEnum btnPress);
	bool ControllerInputPressed(ControllerButtonEnum btnPress);
	bool ControllerInputReleased(ControllerButtonEnum btnPress);

	/*	UPDATES  */
	void Update();
	void UpdatePreviousInput();
	void UpdateController(uint32_t eventType, uint8_t buttonTypeRef);
	void UpdatePreviousController();

	~InputManager();
};
