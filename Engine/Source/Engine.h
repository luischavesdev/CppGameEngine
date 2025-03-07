#pragma once
#include <vector>
#include <string>

class GameEngine
{
private:
	class SDLWrapper* sdl = nullptr;
	class Window* window = nullptr;
	class SDL_Renderer* renderTarget = nullptr;
	class ShaderProgram* myShaderProgram = nullptr;
	class RenderPipeline* myRenderPipeline = nullptr;
	class InputManager* myInputManager = nullptr;
	class PhysicsManager* myPhysManager = nullptr;
	class AudioManager* myAudioManager = nullptr;
	
	class Level* currentLevel = nullptr;
	std::vector<Level*> allLevels{};

	int windowWidth = 0;
	int windowHeight = 0;
	int windowWidthHalf = 0;
	int windowHeightHalf = 0;
	
	bool isRunning = false;
	float frameRate = 0;
	uint8_t tempPadBtnRef = 0;
	uint32_t tempEventType = 0;
	bool hadPadEvent = false;
	unsigned int currentTime = 0;
	unsigned int lastFrameTime = 0;
	double deltaTime = 0;
	float animationSpeedMltplr = 1.0f;


public:
	void CreateControllerInteraction();
	void InitPhysSystem(float PPMRef, float gravityRef, float timeStepRef, int velocityIterationsRef, int positionIterationsRef);

	float MoveConfinedToScreenX(float oldposition, float increment, int spriteWidth);
	float MoveConfinedToScreenY(float oldposition, float increment, int spriteHeight);

	Level* CreateAndAddLevel(std::string levelNameRef);
	void SetCurrentLevel(std::string levelNameRef);

	Window* GetWindow();
	SDL_Renderer* GetRenderTarget();
	ShaderProgram* GetShaderProgram();
	RenderPipeline* GetRenderPipeline();
	InputManager* GetInputManager();
	PhysicsManager* GetPhysManager();
	AudioManager* GetAudioManager();
	Level* GetCurrentLevel();
	inline int GetWindowWidth() { return windowWidth; };
	inline int GetWindowHeight() { return windowHeight; };
	void SetAnimMultiplier(float val);

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Init(std::string windowTitle, int windowWidthRef, int windowHeightRef, int frameRateRef, int numAudioChannels);	
	void Start(bool usePhys);

	~GameEngine();
};
