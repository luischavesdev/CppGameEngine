#include "Loner.h"
#include "Engine.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "EnemyProjectile.h"
#include "RenderObject.h"
#include "Level.h"
#include "Texture.h"
#include "Spaceship.h"

Loner::Loner(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velocityRef,
	Texture* projTextureRef, Texture* altProjTextureRef, Spaceship* spaceshipRef) :Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	velocity = velocityRef;

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
		auto test = &mySpaceshipRef;
		mySpaceshipRef->AddSpaceshipRef(test);
	}

	projectileColSize.x = projectileTexture->GetFrameDimensions().width;
	projectileColSize.y = projectileTexture->GetFrameDimensions().height;
	projectileColPosition.x = 0;
	projectileColPosition.y = 0;
}

void Loner::Start()
{
	GetCollider()->SetVelocity(0, velocity);
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

void Loner::UpdateProjectileData()
{
	projectileColPosition.x = GetLocation().x;
	projectileColPosition.y = GetLocation().y - 50;
}

void Loner::SpawnProjectile()
{
	++projectileID;
	if (projectileID > 70)
	{
		projectileID = 50;
	}

	if (mySpaceshipRef != nullptr)
	{
		projDir.x = mySpaceshipRef->GetLocation().x + 10 - GetLocation().x;
		projDir.y = mySpaceshipRef->GetLocation().y + 10 - GetLocation().y;
		projDirMagn = sqrt(projDir.x * projDir.x + projDir.y * projDir.y);
	}
	else
	{
		projDir.x = -1.0f;
		projDir.y = 0.0f;
		projDirMagn = 1.0f;
	}

	UpdateProjectileData();

	RenderObject* projectileRendObject = new RenderObject(1, projectileID, projectileTexture, GetGameEngine(), 1.0f, 1, 1);
	EnemyProjectile* projectileObj = new EnemyProjectile("EnemyProjectile", projectileRendObject, GetGameEngine(), projectileID, 
		projectileVelocity, altProjectileTexture);
	Collider* projectileCol = new Collider(Collider::Dynamic, projectileColPosition, projectileColSize, GetGameEngine()->GetPhysManager(),
		true, projectileObj);
	projectileObj->SetCollider(projectileCol);
	Vector2 projectileVel;
	projectileVel.x = projDir.x / projDirMagn;
	projectileVel.y = projDir.y / projDirMagn;
	projectileObj->GiveColliderVelocity(projectileVel);

	GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(projectileObj);
}

void Loner::Die()
{
	SetObjectToDestroy();
}

Loner::~Loner()
{
	projectileTexture = nullptr;
	altProjectileTexture = nullptr;
	mySpaceshipRef = nullptr;
}
