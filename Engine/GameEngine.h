#pragma once
#include <string>
#include <algorithm>
#include <vector>


class GameEngine
{
private:
	class SDLWrapper* sdl = nullptr;
	class Window* window = nullptr;
	class SDL_Renderer* renderTarget = nullptr;
	class GameState* myGameState = nullptr;
	int windowWidth;
	int windowHeight;
	int windowWidthHalf;
	int windowHeightHalf;
	class PhysicsManager* myPhysManager;
	std::vector<class Level*> allLevels{};
	Level* currentLevel;
	class RenderPipeline* myRenderPipeline;
	class InputManager* myInputManager;

	class ShaderProgram* myShaderProgram;

	bool isRunning = false;
	uint8_t tempPadBtnRef = 0;
	uint32_t tempEventType = 0;
	bool hadPadEvent = false;
	unsigned int currentTime;
	unsigned int lastFrameTime;
	double deltaTime;


public:
	GameEngine();

	class AudioManager* myAudioManager;

	/* ENGINE EXECUTION */

	int ExitEngine();

	int ExitEngine(int errorNumber);

	int ExitEngine(class Window* windowToExit);

	int ExitEngine(class Window* windowToExit, int errorNumber);


	/* SDL INIT */

	int InitEngineSystems();

	int InitEngineSystems(bool timer, bool audio, bool video, bool gameController);

	int InitEngineSystems(bool video);


	/* BASIC VISUAL CONTAINERS */

	class Window* InitializeWindow(int Xresolution, int Yresolution);

	class Window* InitializeWindow();

	class Window* InitializeWindow(bool fullscreen);


	/*	VISUAL LOADERS  */

	class SDL_Surface* OptimizedSurface(std::string filePath, class SDL_Surface* windowSurface);

	class SDL_Texture* LoadTexture(std::string filePath, class SDL_Renderer* renderTarget);


	//RECTS

	class SDL_Rect CreateRect(int w, int h);

	class SDL_Rect CreateRect(int x, int y, int w, int h);

	class SDL_Rect CreateRect();


	//FRECTS

	class SDL_FRect CreateFRect(int w, int h);

	class SDL_FRect CreateFRect(int x, int y, int w, int h);

	class SDL_FRect CreateFRect();


	/* INPUT MANAGEMENT */

	void CreateControllerInteraction();


	/* TRANSFORMATION */

	float MoveConfinedToScreenX(float oldposition, float increment, int spriteWidth);

	float MoveConfinedToScreenY(float oldposition, float increment, int spriteHeight);


	/* PHYS */

	void InitPhysSystem(float PPMRef, float gravityRef, float timeStepRef, int velocityIterationsRef, int positionIterationsRef);


	/* LEVELS */

	Level* CreateAndAddLevel(std::string levelNameRef);

	void SetCurrentLevel(std::string levelNameRef);


	/* GET FUNCTIONS */

	inline int GetWindowWidth() { return windowWidth; };

	inline int GetWindowHeight() { return windowHeight; };

	PhysicsManager* GetPhysManager();

	SDL_Renderer* GetRenderer();

	Window* GetWindow();

	Level* GetCurrentLevel();

	RenderPipeline* GetRenderPipeline();

	InputManager* GetInputManager();

	ShaderProgram* GetShaderProgram();

	GameState* GetGameState();


	/*   UPDATES   */

	void EarlyUpdate();
	void Update();
	void LateUpdate();


	/*	STARTING THE ENGINE  */

	void Init(std::string windowTitle, int windowWidthRef, int windowHeightRef, int numAudioChannels);

	//Start and choose to run phys or not
	void Start(bool usePhys);

	~GameEngine();
};

