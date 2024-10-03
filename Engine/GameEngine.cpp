#include <iostream>
#include "SDL.h"
#include "box2d/box2d.h"
#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "Texture.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "PhysicsListener.h"
#include "RenderPipeline.h"
#include "Level.h"
#include "InputManager.h"
#include "Object.h"
#include "ShaderProgram.h"
#include "GameState.h"

#include "glad.h"
#include "stb_image.h"

#include "AudioManager.h"


GameEngine::GameEngine()
{

}

int GameEngine::ExitEngine()
{
	SDL_Quit();
	return 0;
}

int GameEngine::ExitEngine(int errorNumber)
{
	SDL_Quit();
	return errorNumber;
}

int GameEngine::ExitEngine(Window* windowToExit)
{
	SDL_DestroyWindow(windowToExit->GetSDLWindow());
	windowToExit = nullptr;
	SDL_Quit();
	return 0;
}

int GameEngine::ExitEngine(Window* windowToExit, int errorNumber)
{
	SDL_DestroyWindow(windowToExit->GetSDLWindow());
	windowToExit = nullptr;
	SDL_Quit();
	return 0;
}


/* SDL INIT */

int GameEngine::InitEngineSystems()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Everything initialization error: " << SDL_GetError() << std::endl;
		return -1;
	}
}

int GameEngine::InitEngineSystems(bool timer, bool audio, bool video, bool gameController)
{
	if (timer)
	{
		if (SDL_Init(SDL_INIT_TIMER) < 0)
		{
			std::cout << "Timer initialization error: " << SDL_GetError() << std::endl;
			return -1;
		}
	}

	if (audio)
	{
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			std::cout << "Audio initialization error: " << SDL_GetError() << std::endl;
			return -1;
		}
	}

	if (video)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Video initialization error: " << SDL_GetError() << std::endl;
			return -1;
		}
	}

	if (gameController)
	{
		if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
		{
			std::cout << "GameController initialization error: " << SDL_GetError() << std::endl;
			return -1;
		}
	}
}

int GameEngine::InitEngineSystems(bool video)
{
	if (video)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Video initialization error: " << SDL_GetError() << std::endl;
			return -1;
		}
		else
		{
			std::cout << "Video";
		}
	}
}

/* BASIC VISUAL CONTAINERS */

Window* GameEngine::InitializeWindow(int Xresolution, int Yresolution)
{
	Window* tempWindow = nullptr;

	tempWindow = new Window("GameName", Xresolution, Yresolution, false);

	if (tempWindow == nullptr)
	{
		std::cout << "Window Creation Error" << SDL_GetError << std::endl;
		ExitEngine(2);
	}

	SDL_DisableScreenSaver();

	return tempWindow;
}

Window* GameEngine::InitializeWindow()
{
	Window* tempWindow = nullptr;

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;

	tempWindow = new Window("GameName", Width, Height, false);

	if (tempWindow == nullptr)
	{
		std::cout << "Window Creation Error" << SDL_GetError << std::endl;
		ExitEngine(2);
	}

	return tempWindow;
}

Window* GameEngine::InitializeWindow(bool fullscreen)
{
	Window* tempWindow = nullptr;

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;

	if (fullscreen == true)
	{
		tempWindow = new Window("GameName", Width, Height, true);
	}
	else
	{
		tempWindow = new Window("GameName", Width, Height, false);
	}

	if (tempWindow == nullptr)
	{
		std::cout << "Window Creation Error" << SDL_GetError << std::endl;
		ExitEngine(2);
	}

	return tempWindow;
}

/*	VISUAL LOADERS  */

SDL_Surface* GameEngine::OptimizedSurface(std::string filePath, SDL_Surface* windowSurface)
{
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error in optimzed surface" << std::endl;
	else
	{
		optimizedSurface = SDL_ConvertSurface(surface, windowSurface->format, 0);
		if (optimizedSurface == NULL)
			std::cout << "Error in optimzed surface" << std::endl;
	}

	SDL_FreeSurface(surface);

	return optimizedSurface;
}

SDL_Texture* GameEngine::LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error No Texture Found" << std::endl;
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error Loading Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

//RECTS

SDL_Rect GameEngine::CreateRect(int w, int h)
{
	SDL_Rect tempRect;
	tempRect.x = tempRect.y = 0;
	tempRect.w = w;
	tempRect.h = h;

	return tempRect;
}

SDL_Rect GameEngine::CreateRect(int x, int y, int w, int h)
{
	SDL_Rect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;

	return tempRect;
}

SDL_Rect GameEngine::CreateRect()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;

	SDL_Rect tempRect;
	tempRect.x = 0;
	tempRect.y = 0;
	tempRect.w = Width;
	tempRect.h = Height;

	return tempRect;
}

//Frects

SDL_FRect GameEngine::CreateFRect(int w, int h)
{
	SDL_FRect tempRect;
	tempRect.x = tempRect.y = 0;
	tempRect.w = w;
	tempRect.h = h;

	return tempRect;
}

SDL_FRect GameEngine::CreateFRect(int x, int y, int w, int h)
{
	SDL_FRect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;

	return tempRect;
}

SDL_FRect GameEngine::CreateFRect()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;

	SDL_FRect tempRect;
	tempRect.x = 0;
	tempRect.y = 0;
	tempRect.w = Width;
	tempRect.h = Height;

	return tempRect;
}


/* INPUT MANAGEMENT */

void GameEngine::CreateControllerInteraction()
{
	SDL_GameController* controller = NULL;
	int iController;
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	for (iController = 0; iController < SDL_NumJoysticks(); ++iController) {
		if (SDL_IsGameController(iController)) {
			char* mapping;
			std::cout << "Index '" << iController << "' is a compatible controller, named '" <<
				SDL_GameControllerNameForIndex(iController) << "'" << std::endl;
			controller = SDL_GameControllerOpen(iController);
			mapping = SDL_GameControllerMapping(controller);
			std::cout << "Controller " << iController << " is mapped as \"" << mapping << std::endl;
			SDL_free(mapping);
		}
		else {
			std::cout << "Index '" << iController << "' is not a compatible controller." << std::endl;
		}
	}
	if (controller == NULL)
	{
		SDL_GameControllerClose(controller); //keyboard only
	}

	std::cout << SDL_GameControllerGetStringForButton(SDL_CONTROLLER_BUTTON_A) << std::endl; // Gives you the mapping name for the specified button
	std::cout << SDL_GameControllerGetStringForAxis(SDL_CONTROLLER_AXIS_RIGHTX) << std::endl; // Gives you the mapping name for the specified axis
}


/* Transformation */

float GameEngine::MoveConfinedToScreenX(float oldposition, float increment, int spriteWidth)
{
	int spriteWidthHalf = spriteWidth / 2;

	if (oldposition + increment < windowWidthHalf - spriteWidthHalf && oldposition + increment > -windowWidthHalf + spriteWidthHalf)
	{
		return oldposition + increment;
	}
	else if (oldposition + increment < -windowWidthHalf + spriteWidthHalf)
	{
		return -windowWidthHalf + spriteWidthHalf;
	}
	else if (oldposition + increment > windowWidthHalf - spriteWidthHalf)
	{
		return windowWidthHalf - spriteWidthHalf;
	}
}

float GameEngine::MoveConfinedToScreenY(float oldposition, float increment, int spriteHeight)
{
	int spriteHeightHalf = spriteHeight / 2;

	if (oldposition - increment < windowHeightHalf - spriteHeightHalf && oldposition - increment > -windowHeightHalf + spriteHeightHalf)
	{
		return oldposition - increment;
	}
	else if (oldposition - increment < -windowHeightHalf + spriteHeightHalf)
	{
		return -windowHeightHalf + spriteHeightHalf;
	}
	else if (oldposition - increment > windowHeightHalf - spriteHeightHalf)
	{
		return windowHeightHalf - spriteHeightHalf;
	}
}


/* PHYS */

void GameEngine::InitPhysSystem(float PPMRef, float gravityRef, float timeStepRef, int velocityIterationsRef, int positionIterationsRef)
{
	myPhysManager = new PhysicsManager(8.0f, this);
	myPhysManager->InitPhysSim(PPMRef, gravityRef, timeStepRef, velocityIterationsRef, positionIterationsRef);
}


/* LEVELS */

Level* GameEngine::CreateAndAddLevel(std::string levelNameRef)
{
	allLevels.push_back(new Level(levelNameRef,  this));

	if (allLevels.size() > 0 && allLevels.size() < 2)
	{
		SetCurrentLevel(levelNameRef);
	}

	return allLevels.at(allLevels.size() - 1);
}

void GameEngine::SetCurrentLevel(std::string levelNameRef)
{
	int iterator = 0;

	if (allLevels.size() > 0)
	{
		for (Level* i : allLevels)
		{
			if (i->GetName() == levelNameRef)
			{
				currentLevel = allLevels.at(iterator);
			}

			++iterator;
		}
	}
}


/* GET FUNCTIONS */

PhysicsManager* GameEngine::GetPhysManager()
{
	if (myPhysManager != nullptr)
	{
		return myPhysManager;
	}
}

SDL_Renderer* GameEngine::GetRenderer()
{
	if (renderTarget != nullptr)
	{
		return renderTarget;
	}
}

Window* GameEngine::GetWindow()
{
	if (window != nullptr)
	{
		return window;
	}
}

Level* GameEngine::GetCurrentLevel()
{
	if (currentLevel != nullptr)
	{
		return currentLevel;
	}
}

RenderPipeline* GameEngine::GetRenderPipeline()
{
	if (myRenderPipeline != nullptr)
	{
		return myRenderPipeline;
	}
}

InputManager* GameEngine::GetInputManager()
{
	if (myInputManager != nullptr)
	{
		return myInputManager;
	}
}

ShaderProgram* GameEngine::GetShaderProgram()
{
	if (myShaderProgram != nullptr)
	{
		return myShaderProgram;
	}
}


GameState* GameEngine::GetGameState()
{
	if (myGameState != nullptr)
	{
		return myGameState;
	}
}

/*   UPDATES   */

void GameEngine::EarlyUpdate()
{
	myPhysManager->RunStep();
}

void GameEngine::Update()
{
	myInputManager->Update();

	if (currentLevel != nullptr)
	{
		currentLevel->Update();
	}
}

void GameEngine::LateUpdate()
{
	myRenderPipeline->PlayRenderPipeline(1.0f);

	myInputManager->UpdatePreviousInput();
}

/*	STARTING THE ENGINE  */

void GameEngine::Init(std::string windowTitle, int windowWidthRef, int windowHeightRef, int numAudioChannels)
{
	windowWidth = windowWidthRef;
	windowHeight = windowHeightRef;
	windowWidthHalf = windowWidth / 2;
	windowHeightHalf = windowHeight / 2;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	window = new Window(windowTitle, windowWidth, windowHeight, false);
	renderTarget = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	myRenderPipeline = new RenderPipeline(this);
	myInputManager = new InputManager();
	myShaderProgram = new ShaderProgram(this);
	myGameState = new GameState(99999.9f);
	myShaderProgram->Start(true, (float)windowWidth / (float)windowHeight);

	myAudioManager = new AudioManager(numAudioChannels);
}

void GameEngine::Start(bool usePhys)
{
	isRunning = true;
	SDL_Event ev;

	currentTime = SDL_GetTicks();
	lastFrameTime = SDL_GetTicks();
	deltaTime = 0;

	while (isRunning)
	{		
		currentTime = SDL_GetTicks();
		deltaTime += currentTime - lastFrameTime;

		if (deltaTime > 1000 / 60.0)
		{
			tempEventType = 0;
			tempPadBtnRef = 0;
			hadPadEvent = false;


			if (usePhys)
			{
				EarlyUpdate();
			}

			while (SDL_PollEvent(&ev) != 0)
			{
				if (ev.type == SDL_QUIT)
				{
					isRunning = false;
				}

				if (ev.type == SDL_CONTROLLERBUTTONDOWN || ev.type == SDL_CONTROLLERBUTTONUP)
				{
					GetInputManager()->UpdateController(ev.type, ev.cbutton.button);

					tempEventType = ev.type;
					tempPadBtnRef = ev.cbutton.button;
					hadPadEvent = true;
				}
			}

			Update();
			LateUpdate();

			if (hadPadEvent)
			{
				GetInputManager()->UpdatePreviousController();
			}

			deltaTime = 0;
		}

		lastFrameTime = SDL_GetTicks();
	}
}

GameEngine::~GameEngine()
{
	delete myPhysManager;

	if (allLevels.size() > 0)
	{
		for (Level* i : allLevels)
		{
			delete i;
		}
	}

	delete sdl;
	delete window;
	SDL_DestroyRenderer(renderTarget);
	SDL_Quit();

	delete myRenderPipeline;
	delete myInputManager;
	delete myShaderProgram;

	currentLevel = nullptr;
	sdl = nullptr;
	window = nullptr;
	renderTarget = nullptr;
	myPhysManager = nullptr;
	myRenderPipeline = nullptr;
	myInputManager = nullptr;
	myShaderProgram = nullptr;
}
