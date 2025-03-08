#include "Spaceship.h"
#include "Engine.h"
#include "Texture.h"
#include "Collider.h"
#include "RenderObject.h"
#include "InputManager.h"
#include "Level.h"
#include "Missile.h"
#include "Companion.h"
#include "AudioManager.h";

Spaceship::Spaceship(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velocityRef, 
	Texture* missileTextureRef, Texture* altMissileTextureRef, Texture* companionTextRef) : Pawn(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	velocity = velocityRef;
	life = maxLife;

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


	missileColSize.x = missileTexture->GetFrameDimensions().width;
	missileColSize.y = missileTexture->GetFrameDimensions().height;
	missileColPosition.x = 0 ;
	missileColPosition.y = 0;

	companionManager[0] = 0;
	companionManager[1] = 0;

	SetRotation(-90.0f);
}

void Spaceship::Start()
{
	SetLocation(0, 0);
}

void Spaceship::Update()
{
	UpdateInputVector();

	SetLocation(GetGameEngine()->MoveConfinedToScreenX(GetLocation().x, 1.0f * velocity * inputVector.x, GetRenderObject()->myTexture->GetFrameDimensions().width),
		GetGameEngine()->MoveConfinedToScreenY(GetLocation().y, 1.0f * velocity * inputVector.y, GetRenderObject()->myTexture->GetFrameDimensions().height));


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

	//Animation Control
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

void Spaceship::UpdateProjectileData()
{
	missileColPosition.x = GetLocation().x + 30;
	missileColPosition.y = GetLocation().y;
}

void Spaceship::UpgradeFirepower()
{
	currentFirepower = std::max(0.0f, std::min(currentFirepower + 1.0f, 3.0f));
}

void Spaceship::AddCompanion()
{
	canSpawnCompanion = true;
	
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

void Spaceship::ChangeLife(float lifeToAdd)
{
	life = std::max(0.0f, std::min(life + lifeToAdd, maxLife));

	if (lifeToAdd < 0)
	{
		GetGameEngine()->GetAudioManager()->PlaySound(0, "data/audio/DamageTaken.wav", 60);
	}

	if (life <= 0.0f)
	{
		GetGameEngine()->GetAudioManager()->PlaySound(0, "data/audio/ShipExplosion.wav", 100);

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
			GetGameEngine()->GetAudioManager()->PlaySoundOnReservedChannel(7, 0, "data/audio/GameOver.wav", 120);
			SetObjectToDestroy();
		}
	}
}

void Spaceship::SpawnMissile()
{
	++missileID;

 	if (missileID > 30)
	{
		missileID = 10;
	}
	
	UpdateProjectileData();


 	RenderObject* missileRendObject = new RenderObject(1, missileID, missileTexture, GetGameEngine(), 1.0f, 1, currentFirepower);
	Missile* testMissile = new Missile("Missile", missileRendObject, GetGameEngine(), missileID, missileVelocity, currentFirepower, 
		explosionTexture);
	Collider* missileCol = new Collider(Collider::Dynamic, missileColPosition, missileColSize, GetGameEngine()->GetPhysManager(),
		true, testMissile);
	testMissile->SetCollider(missileCol);
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
		Vector2 position0;
		position0.x = GetLocation().x;
		position0.y = GetLocation().y;
		Vector2 size0;
		size0.x = companionTexture->GetFrameDimensions().width;
		size0.y = companionTexture->GetFrameDimensions().height;

		Companion* companionShipObj = new Companion("Companion", companionRendObject, GetGameEngine(), companionRendObject->id, missileTexture,
			explosionTexture, this, companionToSpawn);

		if (companionToSpawn == 0)
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

void Spaceship::UpdateInputVector()
{
	inputVector.x = 0;
	inputVector.y = 0;
	

	if ((GetInputManager()->KeyDown(InputManager::RIGHT_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_RIGHT)))
	{
		inputVector.x += 1;
	}

	if ((GetInputManager()->KeyDown(InputManager::LEFT_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_LEFT)))
	{
		inputVector.x -= 1;
	}

	if ((GetInputManager()->KeyDown(InputManager::UP_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_UP)))
	{
		inputVector.y -= 1;
	}

	if ((GetInputManager()->KeyDown(InputManager::DOWN_KEY)) || (GetInputManager()->ControllerInputDown(InputManager::DPAD_DOWN)))
	{
		inputVector.y += 1;
	}

	inputVector.x /= sqrt((inputVector.x * inputVector.x) + (inputVector.y * inputVector.y));
	inputVector.y /= sqrt((inputVector.x * inputVector.x) + (inputVector.y * inputVector.y));

	if (isnan(inputVector.x))
	{
		inputVector.x = 0;
	}
	if (isnan(inputVector.y))
	{
		inputVector.y = 0;
	}
}

void Spaceship::AddSpaceshipRef(Spaceship** pointer) 
{
	spaceshipRefs.push_back(pointer);
}

Spaceship::~Spaceship()
{
	missileTexture = nullptr;
	explosionTexture = nullptr;

	if (spaceshipRefs.size() > 0)
	{
		for (auto ptr : spaceshipRefs)
		{
			*ptr = nullptr;
		}
	}
}
