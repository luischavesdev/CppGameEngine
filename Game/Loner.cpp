#include <iostream>
#include "Loner.h"
#include "Collider.h"
#include "GameEngine.h"
#include "PhysicsManager.h"
#include "EnemyProjectile.h"
#include "RenderObject.h"
#include "Level.h"
#include "Texture.h"
#include "Spaceship.h"
#include "Vector2.h"


Loner::Loner(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velocityRef,
	Texture* projTextureRef, Texture* altProjTextureRef, Spaceship* spaceshipRef) :Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	velocity = velocityRef;
	projectileVelocity = 80.0f;
	spawnTimer = 0;
	timeToSpawn = 50;

	if (projTextureRef != nullptr)
	{
		projectileTexture = projTextureRef;
	}

	if (altProjTextureRef != nullptr)
	{
		altProjectileTexture = altProjTextureRef;
	}

	if (spaceshipRef != nullptr)
	{
		mySpaceshipRef = spaceshipRef;
	}


	projectileColSize[0] = projectileTexture->GetFrameDimensions().width;
	projectileColSize[1] = projectileTexture->GetFrameDimensions().height;
	projectileColPosition[0] = 0;
	projectileColPosition[1] = 0;
}

Vector2 Loner::GetMySpawnLocation()
{
	Vector2 tempSpawnLocation;

	tempSpawnLocation.y = GetLocation().y - 50;
	tempSpawnLocation.x = GetLocation().x;

	return tempSpawnLocation;
}

void Loner::UpdateProjectileData()
{
	projectileColPosition[0] = GetMySpawnLocation().x;
	projectileColPosition[1] = GetMySpawnLocation().y;
}

void Loner::SpawnProjectile()
{
	++projectileID;
	if (projectileID > 70)
	{
		projectileID = 50;
	}

	if (mySpaceshipRef)
	{
		projDir.x = mySpaceshipRef->GetLocation().x + 10 - GetLocation().x;
		projDir.y = mySpaceshipRef->GetLocation().y + 10 - GetLocation().y;
		projDirMagn = sqrt(projDir.x * projDir.x + projDir.y * projDir.y);
	}
	else
	{
		projDir.x = -1.0f;
		projDir.y = -1.0f;
		projDirMagn = 1.0f;
	}

	UpdateProjectileData();

	//Create new Render Obj
	RenderObject* projectileRendObject = new RenderObject(1, projectileID, projectileTexture, GetGameEngine(), 1.0f, 1, 1);

	//Create new Missile
	EnemyProjectile* projectileObj = new EnemyProjectile("EnemyProjectile", projectileRendObject, GetGameEngine(), projectileID, 
		projectileVelocity, altProjectileTexture);
	Collider* projectileCol = new Collider(Collider::Dynamic, projectileColPosition, projectileColSize, GetGameEngine()->GetPhysManager(),
		true, projectileObj);
	projectileObj->SetCollider(projectileCol);
	projectileObj->GiveColliderVelocity(Vector2(projDir.x / projDirMagn, projDir.y / projDirMagn));

	GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(projectileObj);
}

void Loner::Die()
{
	SetObjectToDestroy();
}

void Loner::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));

	if (GetLocation().y > 220)
	{
		GetCollider()->SetVelocity(0, -velocity);
	}
	if (GetLocation().y < -220)
	{
		GetCollider()->SetVelocity(0, velocity);
	}

	
	++spawnTimer;
	if (spawnTimer == timeToSpawn)
	{
		spawnTimer = 0;
		SpawnProjectile();
	}
}

void Loner::Start()
{
	GetCollider()->SetVelocity(0, velocity);
}

Loner::~Loner()
{
	projectileTexture = nullptr;
	altProjectileTexture = nullptr;
	mySpaceshipRef = nullptr;
}