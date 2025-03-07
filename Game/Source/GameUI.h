#pragma once
#include "Object.h"

class GameUI : public Object 
{
private:
	class RenderObject* healthBar = nullptr;
	RenderObject* shipLives = nullptr;

	class Spaceship* mySpaceshipRef = nullptr;


public:
	GameUI(std::string objectNameRef, RenderObject* healthBarRef, RenderObject* shipLivesRef, GameEngine* gameEngineRef, Spaceship* spaceshipRef, 
		int idRef);

	void Start() override;
	void Update() override;

	RenderObject* GetHealthBar();
	RenderObject* GetShipLives();

	~GameUI();
};
