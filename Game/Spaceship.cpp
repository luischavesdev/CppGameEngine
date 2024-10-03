#include <iostream>
#include <iomanip>
#include "Spaceship.h"
#include "GameEngine.h"
#include "InputManager.h"
#include "RenderObject.h"
#include "RectValues.h"
#include "Level.h"
#include "Collider.h"
#include "Texture.h"
#include "Missile.h"
#include "PhysicsManager.h"
#include "Companion.h"

#include "AudioManager.h";

Spaceship::Spaceship(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velocityRef, 
	Texture* missileTextureRef, Texture* altMissileTextureRef, Texture* companionTextRef) : Pawn(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	velocity = velocityRef;
	missileVelocity = 100.0f;
	maxLife = 8.0f;
	life = maxLife;
	currentFirepower = 1.0f;
	extraLives = 2;


	if (missileTextureRef)
	{
		missileTexture = missileTextureRef;
	}

	if (altMissileTextureRef)
	{
		explosionTexture = altMissileTextureRef;
	}

	if (companionTextRef)
	{
		companionTexture = companionTextRef;
	}


	missileColSize[0] = missileTexture->GetFrameDimensions().width;
	missileColSize[1] = missileTexture->GetFrameDimensions().height;
	missileColPosition[0] = 0 ;
	missileColPosition[1] = 0;

	companionManager[0] = 0;
	companionManager[1] = 0;

	SetRotation(-90.0f);
}

Vector2 Spaceship::getInputVector()
{
	Vector2 vec = Vector2(0, 0);

	if ((GetInputManager()->KeyDown(InputManager::RIGHT_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_RIGHT)))
	{
		vec.x += 1;
	}

	if ((GetInputManager()->KeyDown(InputManager::LEFT_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_LEFT)))
	{
		vec.x -= 1;
	}

	if ((GetInputManager()->KeyDown(InputManager::UP_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_UP)))
	{
		vec.y -= 1;
	}

	if ((GetInputManager()->KeyDown(InputManager::DOWN_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_DOWN)))
	{
		vec.y += 1;
	}

	vec.x /= sqrt((vec.x * vec.x) + (vec.y * vec.y));
	vec.y /= sqrt((vec.x * vec.x) + (vec.y * vec.y));

	if (isnan(vec.x))
	{
		vec.x = 0;
	}
	if (isnan(vec.y))
	{
		vec.y = 0;
	}
	
	return vec;
}

Spaceship::SpawnLocation Spaceship::GetMySpawnLocation()
{
	SpawnLocation tempSpawnLocation;

	tempSpawnLocation.yPos = GetLocation().y;
	tempSpawnLocation.xPos = GetLocation().x +30;

	return tempSpawnLocation;
}

void Spaceship::UpdateProjectileData()
{
	missileColPosition[0] = GetMySpawnLocation().xPos;
	missileColPosition[1] = GetMySpawnLocation().yPos;
}

void Spaceship::SpawnMissile()
{
	++missileID;

	if (missileID > 30)
	{
		missileID = 10;
	}
	
	UpdateProjectileData();

	//Create new Render Obj
	RenderObject* missileRendObject = new RenderObject(1, missileID, missileTexture, GetGameEngine(), 1.0f, 1, currentFirepower);

	//Create new Missile
	Missile* testMissile = new Missile("Missile", missileRendObject, GetGameEngine(), missileID, missileVelocity, currentFirepower, 
		explosionTexture);
	Collider* missileCol = new Collider(Collider::Dynamic, missileColPosition, missileColSize, GetGameEngine()->GetPhysManager(),
		true, testMissile);
	testMissile->SetCollider(missileCol);
	testMissile->Start();
	GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(testMissile);
}

void Spaceship::SpawnCompanion()
{
	int companionToSpawn = -1;

	if (!companionManager[0])
	{
		companionManager[0] = 1;
		companionToSpawn = 0;
	}
	else if (!companionManager[1])
	{
		companionManager[1] = 1;
		companionToSpawn = 1;
	}

	if (companionToSpawn == 0 || companionToSpawn == 1)
	{
		RenderObject* companionRendObject = new RenderObject(1, missileID, companionTexture, GetGameEngine(), 1.0f, 1, 1);
		float position0[2] = { GetLocation().x, GetLocation().y };
		float size0[2] = { companionTexture->GetFrameDimensions().width, companionTexture->GetFrameDimensions().height };

		Companion* companionShipObj = new Companion("Companion", companionRendObject, GetGameEngine(), companionRendObject->id, missileTexture,
			explosionTexture, this, companionToSpawn);

		if (!companionToSpawn)
		{
			myCompanionRef0 = companionShipObj;
		}
		else
		{
			myCompanionRef1 = companionShipObj;
		}
		
		Collider* companionShipCol = new Collider(Collider::Dynamic, position0, size0, GetGameEngine()->GetPhysManager(), true, companionShipObj);
		companionShipObj->SetCollider(companionShipCol);

		GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(companionShipObj);
	}
}

void Spaceship::ChangeLife(float lifeToAdd)
{
	life = std::max(0.0f, std::min(life + lifeToAdd, maxLife));

	GetGameEngine()->myAudioManager->PlaySound(0, "audio/DamageTaken.wav", 60);
	
	if (life <= 0.0f)
	{

		GetGameEngine()->myAudioManager->PlaySound(0, "audio/ShipExplosion.wav", 100);

		extraLives -= 1;
		life = maxLife;
		if (extraLives <= -1)
		{
			if (companionManager[0])
			{
				myCompanionRef0->SetObjectToDestroy();
			}

			if (companionManager[1])
			{
				myCompanionRef1->SetObjectToDestroy();
			}
			GetGameEngine()->myAudioManager->PlaySoundOnReservedChannel(7, 0, "audio/GameOver.wav", 120);
			SetObjectToDestroy();
		}
	}
}

void Spaceship::UpgradeFirepower()
{
	currentFirepower = std::max(0.0f, std::min(currentFirepower + 1.0f, 3.0f));
	GetGameEngine()->myAudioManager->PlaySound(0, "audio/PowerupAcquired.wav", 60);
}

void Spaceship::AddCompanion()
{
	canSpawnCompanion = true;

	GetGameEngine()->myAudioManager->PlaySound(0, "audio/PowerupAcquired.wav", 60);
}

void Spaceship::UpdateCompanionStatus(int companionRef, bool trueFalse)
{
	if (!companionRef)
	{
		companionManager[0] = trueFalse;

		if (!trueFalse)
		{
			myCompanionRef0 = nullptr;
		}
	}
	else
	{
		companionManager[1] = trueFalse;

		if (!trueFalse)
		{
			myCompanionRef1 = nullptr;
		}
	}
}

void Spaceship::Update()
{

	SetLocation(GetGameEngine()->MoveConfinedToScreenX(GetLocation().x, 1.0f * velocity * getInputVector().x, GetRenderObject()->myTexture->GetFrameDimensions().width), 
		GetGameEngine()->MoveConfinedToScreenY(GetLocation().y, 1.0f * velocity * getInputVector().y, GetRenderObject()->myTexture->GetFrameDimensions().height));


	GetCollider()->SetLocation(GetLocation().x, GetLocation().y);



	if (GetInputManager()->KeyPressed(InputManager::SPACE_KEY) || (GetInputManager()->ControllerInputPressed(InputManager::BTN_A)))
	{
		SpawnMissile();

		if (companionManager[0] == 1)
		{
			myCompanionRef0->SpawnMissile();
		}
		
		if (companionManager[1] == 1)
		{
			myCompanionRef1->SpawnMissile();
		}
	}


	if (canSpawnCompanion == true)
	{
		canSpawnCompanion = false;
		SpawnCompanion();
	}



	/* ANIMATION CONTROL */
	if ((GetInputManager()->KeyPressed(InputManager::DOWN_KEY)) || (GetInputManager()->ControllerInputPressed(InputManager::DPAD_DOWN)))
	{
		if (GetRenderObject()->currentColumn != 7)
		{
			GetRenderObject()->PauseAnimation(false);
			GetRenderObject()->ReverseAnimation(false);
		}
	}

	if (GetInputManager()->KeyPressed(InputManager::UP_KEY) || GetInputManager()->ControllerInputPressed(InputManager::DPAD_UP))
	{
		if (GetRenderObject()->currentColumn != 1)
		{
			GetRenderObject()->PauseAnimation(false);
			GetRenderObject()->ReverseAnimation(true);
		}
	}

	if ((GetInputManager()->KeyDown(InputManager::DOWN_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_DOWN)))
	{
		if (GetRenderObject()->currentColumn == 7)
		{
			GetRenderObject()->PauseAnimation(true);
			GetRenderObject()->ReverseAnimation(false);
		}
	}

	if (GetInputManager()->KeyDown(InputManager::UP_KEY) || GetInputManager()->ControllerInputDown(InputManager::DPAD_UP))
	{
		if (GetRenderObject()->currentColumn == 1)
		{
			GetRenderObject()->PauseAnimation(true);
			GetRenderObject()->ReverseAnimation(false);
		}
	}

	if (GetInputManager()->KeyReleased(InputManager::DOWN_KEY) || GetInputManager()->ControllerInputReleased(InputManager::DPAD_DOWN))
	{
		if (GetRenderObject()->currentColumn > 4)
		{
			GetRenderObject()->PauseAnimation(false);
			GetRenderObject()->ReverseAnimation(true);
		}
	}

	if (GetInputManager()->KeyReleased(InputManager::UP_KEY) || GetInputManager()->ControllerInputReleased(InputManager::DPAD_UP))
	{
		if (GetRenderObject()->currentColumn < 4)
		{
			GetRenderObject()->PauseAnimation(false);
			GetRenderObject()->ReverseAnimation(false);
		}
	}

	if (
		((!GetInputManager()->ControllerInputDown(InputManager::DPAD_UP) && !GetInputManager()->ControllerInputDown(InputManager::DPAD_DOWN)) ||
			GetInputManager()->ControllerInputDown(InputManager::DPAD_UP) && GetInputManager()->ControllerInputDown(InputManager::DPAD_DOWN))
		&&
		((!GetInputManager()->KeyDown(InputManager::UP_KEY) && !GetInputManager()->KeyDown(InputManager::DOWN_KEY)) ||
			GetInputManager()->KeyDown(InputManager::UP_KEY) && GetInputManager()->KeyDown(InputManager::DOWN_KEY))
		)
	{
		if (GetRenderObject()->currentColumn == 4)
		{
			GetRenderObject()->PauseAnimation(true);
		}
	}
}

void Spaceship::Start()
{
	SetLocation(0, 0);
}

Spaceship::~Spaceship()
{
	missileTexture = nullptr;
	explosionTexture = nullptr;
}
