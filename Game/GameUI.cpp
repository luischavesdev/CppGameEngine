#include <iostream>
#include "GameUI.h"
#include "GameEngine.h"
#include "Texture.h"
#include "RenderPipeline.h"
#include "RenderObject.h"
#include "Spaceship.h"

GameUI::GameUI(std::string objectNameRef, RenderObject* healthBarRef, RenderObject* shipLivesRef, GameEngine* gameEngineRef, 
	Spaceship* SpaceshipRef, int idRef) : Object(objectNameRef, gameEngineRef, idRef)
{
	if (healthBarRef != nullptr)
	{
		healthBar = healthBarRef;
	}

	if (shipLivesRef != nullptr)
	{
		shipLives = shipLivesRef;
	}

	if (SpaceshipRef != nullptr)
	{
		mySpaceshipRef = SpaceshipRef;
	}
}

RenderObject* GameUI::GetHealthBar()
{
	if (healthBar != nullptr)
	{
		return healthBar;
	}
}

RenderObject* GameUI::GetShipLives()
{
	if (shipLives != nullptr)
	{
		return shipLives;
	}
}

void GameUI::Update()
{
	
	if (mySpaceshipRef->GetLife() > 5)
	{
		healthBar->SetColorOverlay(0.0f, 1.0f, 0.0f);
	}
	else if (mySpaceshipRef->GetLife() > 2)
	{
		healthBar->SetColorOverlay(1.0f, 1.0f, 0.0f);
	}
	else
	{
		healthBar->SetColorOverlay(1.0f, 0.0f, 0.0f);
	}

	healthBar->yTile = mySpaceshipRef->GetLife();


	shipLives->yTile = mySpaceshipRef->GetExtraLives();
}

void GameUI::Start()
{
	
}

void GameUI::DeleteRenderObjects()
{
	delete shipLives;
	delete healthBar;
}

GameUI::~GameUI()
{

}
