#pragma once
#include <string>
#include <vector>
#include "Object.h"

class GameUI : public Object 
{
private:
	class RenderObject* healthBar = nullptr;
	RenderObject* shipLives = nullptr;

	class Spaceship* mySpaceshipRef;


public:
	GameUI(std::string objectNameRef, RenderObject* healthBarRef, RenderObject* shipLivesRef, GameEngine* gameEngineRef, Spaceship* SpaceshipRef, 
		int idRef);

	RenderObject* GetHealthBar();

	RenderObject* GetShipLives();

	void Update() override;

	void Start() override;

	void DeleteRenderObjects();

	~GameUI();
};