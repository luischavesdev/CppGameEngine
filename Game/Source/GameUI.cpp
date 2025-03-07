#include "GameUI.h"
#include "Engine.h"
#include "RenderObject.h"
#include "RenderPipeline.h"
#include "Spaceship.h"

GameUI::GameUI(std::string objectNameRef, RenderObject* healthBarRef, RenderObject* shipLivesRef, GameEngine* gameEngineRef, 
	Spaceship* spaceshipRef, int idRef) : Object(objectNameRef, gameEngineRef, idRef)
{
	if (healthBarRef != nullptr)
	{
		healthBar = healthBarRef;
	}

	if (shipLivesRef != nullptr)
	{
		shipLives = shipLivesRef;
	}

	if (spaceshipRef != nullptr)
	{
		mySpaceshipRef = spaceshipRef;
		auto test = &mySpaceshipRef;
		mySpaceshipRef->AddSpaceshipRef(test);
	}
}

void GameUI::Start()
{

}

void GameUI::Update()
{
	if (mySpaceshipRef != nullptr)
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

		Vector2 healthTile;
		Vector2 livesTile;
		healthTile.y = mySpaceshipRef->GetLife();
		livesTile.y = mySpaceshipRef->GetExtraLives();

		healthBar->tileMltplr = healthTile;
		shipLives->tileMltplr = livesTile;
	}
	else
	{
		SetObjectToDestroy();
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

GameUI::~GameUI()
{
	GetGameEngine()->GetRenderPipeline()->UnloadRenderObject(shipLives);
	GetGameEngine()->GetRenderPipeline()->UnloadRenderObject(healthBar);
		
	shipLives = nullptr;
	healthBar = nullptr;
}
