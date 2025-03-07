#include <cstring>
#include "SDL.h"

#include "InputManager.h"

InputManager::InputManager()
{	
	myKeyboardState = SDL_GetKeyboardState(&myKeyLength);

	myPreviousKeyboardState = new uint8_t[myKeyLength];
	memcpy(myPreviousKeyboardState, myKeyboardState, myKeyLength);
}

// --- || Key Management || ---

bool InputManager::KeyDown(KeyboardKeysEnum keyPress)
{
	Uint32 mask = 0;

	switch (keyPress)
	{
	case W_KEY:
		mask = SDL_SCANCODE_W;
		break;

	case A_KEY:
		mask = SDL_SCANCODE_A;
		break;

	case S_KEY:
		mask = SDL_SCANCODE_S;
		break;

	case D_KEY:
		mask = SDL_SCANCODE_D;
		break;

	case UP_KEY :
		mask = SDL_SCANCODE_UP;
		break;

	case LEFT_KEY:
		mask = SDL_SCANCODE_LEFT;
		break;

	case DOWN_KEY:
		mask = SDL_SCANCODE_DOWN;
		break;

	case RIGHT_KEY:
		mask = SDL_SCANCODE_RIGHT;
		break;

	case SPACE_KEY:
		mask = SDL_SCANCODE_SPACE;
		break;

	case L_CTRL_KEY:
		mask = SDL_SCANCODE_LCTRL;
		break;

	case L_SHFT_KEY:
		mask = SDL_SCANCODE_LSHIFT;
		break;
	}

	return myKeyboardState[mask];
}

bool InputManager::KeyPressed(KeyboardKeysEnum keyPress)
{
	Uint32 mask = 0;

	switch (keyPress)
	{
	case W_KEY:
		mask = SDL_SCANCODE_W;
		break;

	case A_KEY:
		mask = SDL_SCANCODE_A;
		break;

	case S_KEY:
		mask = SDL_SCANCODE_S;
		break;

	case D_KEY:
		mask = SDL_SCANCODE_D;
		break;

	case UP_KEY:
		mask = SDL_SCANCODE_UP;
		break;

	case LEFT_KEY:
		mask = SDL_SCANCODE_LEFT;
		break;

	case DOWN_KEY:
		mask = SDL_SCANCODE_DOWN;
		break;

	case RIGHT_KEY:
		mask = SDL_SCANCODE_RIGHT;
		break;

	case SPACE_KEY:
		mask = SDL_SCANCODE_SPACE;
		break;

	case L_CTRL_KEY:
		mask = SDL_SCANCODE_LCTRL;
		break;

	case L_SHFT_KEY:
		mask = SDL_SCANCODE_LSHIFT;
		break;
	}

	return !myPreviousKeyboardState[mask] && myKeyboardState[mask];
}

bool InputManager::KeyReleased(KeyboardKeysEnum keyPress)
{
	Uint32 mask = 0;

	switch (keyPress)
	{
	case W_KEY:
		mask = SDL_SCANCODE_W;

		break;

	case A_KEY:
		mask = SDL_SCANCODE_A;
		break;

	case S_KEY:
		mask = SDL_SCANCODE_S;
		break;

	case D_KEY:
		mask = SDL_SCANCODE_D;
		break;

	case UP_KEY:
		mask = SDL_SCANCODE_UP;
		break;

	case LEFT_KEY:
		mask = SDL_SCANCODE_LEFT;
		break;

	case DOWN_KEY:
		mask = SDL_SCANCODE_DOWN;
		break;

	case RIGHT_KEY:
		mask = SDL_SCANCODE_RIGHT;
		break;

	case SPACE_KEY:
		mask = SDL_SCANCODE_SPACE;
		break;

	case L_CTRL_KEY:
		mask = SDL_SCANCODE_LCTRL;
		break;

	case L_SHFT_KEY:
		mask = SDL_SCANCODE_LSHIFT;
		break;
	}

	return myPreviousKeyboardState[mask] && !myKeyboardState[mask];
}

// --- || Mouse Management || ---

bool InputManager::MouseButtonDown(MouseButtonEnum button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;

	case middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (myMouseState & mask);
}

bool InputManager::MouseButtonPressed(MouseButtonEnum button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;

	case middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return !(myPreviousMouseState & mask) && (myMouseState & mask);
}

bool InputManager::MouseButtonReleased(MouseButtonEnum button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;

	case middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (myPreviousMouseState & mask) && !(myMouseState & mask);
}

InputManager::MousePos InputManager::CurrentMousePosition()
{
	return myMousePosition;
}

// --- || Controller Management || ---

bool InputManager::ControllerInputDown(ControllerButtonEnum btnPress)
{
	bool currentBtn = false;

	switch (btnPress)
	{
	case DPAD_LEFT:
		currentBtn = myControllerState.DpadLeft;
		break;

	case DPAD_RIGHT:
		currentBtn = myControllerState.padRight;
		break;

	case DPAD_DOWN:
		currentBtn = myControllerState.DpadDown;
		break;

	case DPAD_UP:
		currentBtn = myControllerState.DpadUp;
		break;

	case BTN_A:
		currentBtn = myControllerState.BtnA;
		break;
	}

	return currentBtn;
}

bool InputManager::ControllerInputPressed(ControllerButtonEnum btnPress)
{
	bool currentBtn = false;
	bool previousBtn = false;

	switch (btnPress)
	{
	case DPAD_LEFT:
		currentBtn = myControllerState.DpadLeft;
		previousBtn = myPreviousControllerState.DpadLeft;
		break;

	case DPAD_RIGHT:
		currentBtn = myControllerState.padRight;
		previousBtn = myPreviousControllerState.padRight;
		break;

	case DPAD_DOWN:
		currentBtn = myControllerState.DpadDown;
		previousBtn = myPreviousControllerState.DpadDown;
		break;

	case DPAD_UP:
		currentBtn = myControllerState.DpadUp;
		previousBtn = myPreviousControllerState.DpadUp;
		break;

	case BTN_A:
		currentBtn = myControllerState.BtnA;
		previousBtn = myPreviousControllerState.BtnA;
		break;
	}

	return !previousBtn && currentBtn;
}

bool InputManager::ControllerInputReleased(ControllerButtonEnum btnPress)
{
	bool currentBtn = false;
	bool previousBtn = false;

	switch (btnPress)
	{
	case DPAD_LEFT:
		currentBtn = myControllerState.DpadLeft;
		previousBtn = myPreviousControllerState.DpadLeft;
		break;

	case DPAD_RIGHT:
		currentBtn = myControllerState.padRight;
		previousBtn = myPreviousControllerState.padRight;
		break;

	case DPAD_DOWN:
		currentBtn = myControllerState.DpadDown;
		previousBtn = myPreviousControllerState.DpadDown;
		break;

	case DPAD_UP:
		currentBtn = myControllerState.DpadUp;
		previousBtn = myPreviousControllerState.DpadUp;
		break;

	case BTN_A:
		currentBtn = myControllerState.BtnA;
		previousBtn = myPreviousControllerState.BtnA;
		break;
	}

	return previousBtn && !currentBtn;
}

// --- || Updates || ---

void InputManager::Update()
{
	myMouseState = SDL_GetMouseState(&myMousePosition.MouseXPos, &myMousePosition.MouseYPos);
}

void InputManager::UpdatePreviousInput()
{
	memcpy(myPreviousKeyboardState, myKeyboardState, myKeyLength);
	myPreviousMouseState = myMouseState;
}

void InputManager::UpdateController(uint32_t eventType, uint8_t buttonTypeRef)
{
	if (eventType == SDL_CONTROLLERBUTTONDOWN)
	{
		switch (buttonTypeRef)
		{
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			myControllerState.DpadLeft = true;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			myControllerState.padRight = true;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			myControllerState.DpadUp = true;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			myControllerState.DpadDown = true;
			break;
		case SDL_CONTROLLER_BUTTON_A:
			myControllerState.BtnA = true;
			break;
		}
	}

	if (eventType == SDL_CONTROLLERBUTTONUP)
	{
		switch (buttonTypeRef)
		{
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			myControllerState.DpadLeft = false;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			myControllerState.padRight = false;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			myControllerState.DpadUp = false;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			myControllerState.DpadDown = false;
			break;
		case SDL_CONTROLLER_BUTTON_A:
			myControllerState.BtnA = false;
			break;
		}
	}
}

void InputManager::UpdatePreviousController()
{
	myPreviousControllerState = myControllerState;
}

InputManager::~InputManager()
{
	delete[] myPreviousKeyboardState;
	myPreviousKeyboardState = nullptr;
	myKeyboardState = nullptr;
}
