#include <iostream>
#include <iomanip>
#include "Companion.h"
#include "GameEngine.h"
#include "InputManager.h"
#include "RenderObject.h"
#include "RectValues.h"
#include "Level.h"
#include "Collider.h"
#include "Texture.h"
#include "Missile.h"
#include "PhysicsManager.h"
#include "Spaceship.h"

Companion::Companion(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, 
	Texture* missileTextureRef, Texture* altMissileTextureRef, Spaceship* spaceshipRef, int companionRef) :Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	missileVelocity = 100.0f;
	maxLife = 3.0f;
	life = maxLife;
	currentFirepower = 1.0f;

	if (spaceshipRef != nullptr)
	{
		mySpaceshipRef = spaceshipRef;
	}

	if (missileTextureRef)
	{
		missileTexture = missileTextureRef;
	}

	if (altMissileTextureRef)
	{
		explosionTexture = altMissileTextureRef;
	}


	missileColSize[0] = missileTexture->GetFrameDimensions().width;
	missileColSize[1] = missileTexture->GetFrameDimensions().height;
	missileColPosition[0] = 0;
	missileColPosition[1] = 0;

	myCompanionRef = companionRef;
	shipOffset = 50.0f;

	if (myCompanionRef)
	{
		shipOffset *= -1;
	}
}

Companion::SpawnLocation Companion::GetMySpawnLocation()
{
	SpawnLocation tempSpawnLocation;

	tempSpawnLocation.yPos = GetLocation().y;
	tempSpawnLocation.xPos = GetLocation().x + 30;

	return tempSpawnLocation;
}

void Companion::UpdateProjectileData()
{
	missileColPosition[0] = GetMySpawnLocation().xPos;
	missileColPosition[1] = GetMySpawnLocation().yPos;
}

void Companion::SpawnMissile()
{
	++missileID;

	if (missileID > 120)
	{
		missileID = 90;
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

void Companion::ChangeLife(float lifeToAdd)
{
	life = std::max(0.0f, std::min(life + lifeToAdd, maxLife));

	//std::cout << "life:" << life << "\n";

	if (life <= 0.0f)
	{
		mySpaceshipRef->UpdateCompanionStatus(myCompanionRef, false);
		SetObjectToDestroy();
	}
}

void Companion::UpgradeFirepower()
{
	currentFirepower = std::max(0.0f, std::min(currentFirepower + 1.0f, 3.0f));
}

void Companion::Update()
{
	SetLocation(mySpaceshipRef->GetLocation().x, mySpaceshipRef->GetLocation().y + shipOffset);


	if (GetRenderObject()->currentColumn >= 4 && GetRenderObject()->currentLine >= 4)
	{
		GetRenderObject()->SkipToFrame(1, 1);
	}

	GetCollider()->SetLocation(GetLocation().x, GetLocation().y);
}

void Companion::Start()
{

}

Companion::~Companion()
{
	missileTexture = nullptr;
	explosionTexture = nullptr;
	mySpaceshipRef = nullptr;
}
