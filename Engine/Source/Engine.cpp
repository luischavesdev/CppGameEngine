#include "SDL.h"

#include "Engine.h"
#include "Logger.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "PhysicsManager.h"
#include "RenderPipeline.h"
#include "Level.h"
#include "InputManager.h"
#include "ShaderProgram.h"
#include "AudioManager.h"

void GameEngine::CreateControllerInteraction()
{
	SDL_GameController* controller = nullptr;
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	for (int iController = 0; iController < SDL_NumJoysticks(); ++iController) {
		if (SDL_IsGameController(iController)) {
			char* mapping;
			CUSTOM_LOGGER("ControllerName:");
			CUSTOM_LOGGER(SDL_GameControllerNameForIndex(iController));

			controller = SDL_GameControllerOpen(iController);
			mapping = SDL_GameControllerMapping(controller);
			CUSTOM_LOGGER("ControllerMapping:");
			CUSTOM_LOGGER(mapping);

			SDL_free(mapping);
		}
		else {
			CUSTOM_LOGGER("ERROR: No compatible controller.");
		}
	}
	if (controller == nullptr)
	{
		SDL_GameControllerClose(controller); //keyboard only
	}
}

void GameEngine::InitPhysSystem(float PPMRef, float gravityRef, float timeStepRef, int velocityIterationsRef, int positionIterationsRef)
{
	myPhysManager = new PhysicsManager(this, PPMRef, gravityRef, timeStepRef, velocityIterationsRef, positionIterationsRef);
	myPhysManager->InitPhysSim();
}

// --- || Object Movement || ---

float GameEngine::MoveConfinedToScreenX(float oldposition, float increment, int spriteWidth)
{
	int spriteWidthHalf = spriteWidth / 2;

	if (oldposition + increment < windowWidthHalf - spriteWidthHalf && oldposition + increment > -windowWidthHalf + spriteWidthHalf)
	{
		return oldposition + increment;
	}
	else if (oldposition + increment <= -windowWidthHalf + spriteWidthHalf)
	{
		return -windowWidthHalf + spriteWidthHalf;
	}
	else if (oldposition + increment >= windowWidthHalf - spriteWidthHalf)
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
	else if (oldposition - increment <= -windowHeightHalf + spriteHeightHalf)
	{
		return -windowHeightHalf + spriteHeightHalf;
	}
	else if (oldposition - increment >= windowHeightHalf - spriteHeightHalf)
	{
		return windowHeightHalf - spriteHeightHalf;
	}
}

// --- || Levels Management || ---

Level* GameEngine::CreateAndAddLevel(std::string levelNameRef)
{
	allLevels.push_back(new Level(levelNameRef, this));

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

// --- || Getters || ---

Window* GameEngine::GetWindow()
{
	if (window != nullptr)
	{
		return window;
	}
}

SDL_Renderer* GameEngine::GetRenderTarget()
{
	if (renderTarget != nullptr)
	{
		return renderTarget;
	}
}

ShaderProgram* GameEngine::GetShaderProgram()
{
	if (myShaderProgram != nullptr)
	{
		return myShaderProgram;
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

PhysicsManager* GameEngine::GetPhysManager()
{
	if (myPhysManager != nullptr)
	{
		return myPhysManager;
	}
}

AudioManager* GameEngine::GetAudioManager()
{
	if (myAudioManager != nullptr)
	{
		return myAudioManager;
	}
}

Level* GameEngine::GetCurrentLevel()
{
	if (currentLevel != nullptr)
	{
		return currentLevel;
	}
}

void GameEngine::SetAnimMultiplier(float val) 
{
	animationSpeedMltplr = val;
}

// --- || Updates || ---

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
	myRenderPipeline->PlayRenderPipeline(animationSpeedMltplr);

	myInputManager->UpdatePreviousInput();
}

// --- || Engine Initialization || ---

void GameEngine::Init(std::string windowTitle, int windowWidthRef, int windowHeightRef, int frameRateRef, int numAudioChannels)
{
	windowWidth = windowWidthRef;
	windowHeight = windowHeightRef;
	windowWidthHalf = windowWidth / 2;
	windowHeightHalf = windowHeight / 2;

	frameRate = frameRateRef;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	window = new Window(windowTitle, windowWidth, windowHeight, false);
	renderTarget = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	myShaderProgram = new ShaderProgram(this);
	myShaderProgram->Start(true, (float)windowWidth / (float)windowHeight);
	myRenderPipeline = new RenderPipeline(this);
	myInputManager = new InputManager();

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

		if (deltaTime > 1000 / frameRate) // The 1000 magic number is because deltaTime is in miliseconds
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
					CUSTOM_LOGGER("SDL QUIT");
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

	delete myShaderProgram;
	delete myRenderPipeline;
	delete myInputManager;
	
	myPhysManager = nullptr;
	currentLevel = nullptr;
	sdl = nullptr;
	window = nullptr;
	renderTarget = nullptr;
	myShaderProgram = nullptr;
	myRenderPipeline = nullptr;
	myInputManager = nullptr;
}
