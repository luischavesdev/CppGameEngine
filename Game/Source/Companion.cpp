#include "Companion.h"
#include "Engine.h"
#include "InputManager.h"
#include "RenderObject.h"
#include "Level.h"
#include "Collider.h"
#include "Texture.h"
#include "Missile.h"
#include "PhysicsManager.h"
#include "Spaceship.h"

Companion::Companion(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, 
	Texture* missileTextureRef, Texture* altMissileTextureRef, Spaceship* spaceshipRef, int companionRef) :Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	life = maxLife;

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

	missileColSize.x = missileTexture->GetFrameDimensions().width;
	missileColSize.y = missileTexture->GetFrameDimensions().height;
	missileColPosition.x = 0;
	missileColPosition.y = 0;

	myCompanionRef = companionRef;

	if (myCompanionRef)
	{
		shipOffset *= -1;
	}
}

void Companion::Start()
{

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

void Companion::ChangeLife(float lifeToAdd)
{
	life = std::max(0.0f, std::min(life + lifeToAdd, maxLife));

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

void Companion::UpdateSpawnLocation()
{
	missileColPosition.x = GetLocation().x + 30;
	missileColPosition.y = GetLocation().y;
}

void Companion::SpawnMissile()
{
	++missileID;

	if (missileID > 120)
	{
		missileID = 90;
	}

	UpdateSpawnLocation();

	RenderObject* missileRendObject = new RenderObject(1, missileID, missileTexture, GetGameEngine(), 1.0f, 1, currentFirepower);
	Missile* testMissile = new Missile("Missile", missileRendObject, GetGameEngine(), missileID, missileVelocity, currentFirepower,
		explosionTexture);
	Collider* missileCol = new Collider(Collider::Dynamic, missileColPosition, missileColSize, GetGameEngine()->GetPhysManager(),
		true, testMissile);
	testMissile->SetCollider(missileCol);
	GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(testMissile);
}

Companion::~Companion()
{
	missileTexture = nullptr;
	explosionTexture = nullptr;
	mySpaceshipRef = nullptr;
}
