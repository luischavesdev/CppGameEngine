#include <iostream>
#include "EnemyProjectile.h"
#include "Level.h"
#include "Collider.h"
#include "GameEngine.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Texture.h"
#include "Spaceship.h"
#include "Companion.h"
#include "Vector2.h"

EnemyProjectile::EnemyProjectile(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef,
	float speedRef, Texture* explosionTextRef) : Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	speed = speedRef;
	lifeCounter = 0;
	lifetime = 50;

	if (explosionTextRef != nullptr)
	{
		explosionTexture = explosionTextRef;
	}
}

void EnemyProjectile::OnCollision(Sprite* colliderSpriteRef)
{
	if (colliderSpriteRef != nullptr)
	{
		Spaceship* spaceshipRef = static_cast<Spaceship*>(colliderSpriteRef);
		if (spaceshipRef->GetName() == "Spaceship")
		{
			GetCollider()->SetVelocity(0, 0);
			GetRenderObject()->ReplaceTexture(explosionTexture, 1, 1);
			spaceshipRef->ChangeLife(-1.0f);
		}
		else
		{
			Companion* companionRef = static_cast<Companion*>(colliderSpriteRef);
			if (companionRef->GetName() == "Companion")
			{
				GetCollider()->SetVelocity(0, 0);
				GetRenderObject()->ReplaceTexture(explosionTexture, 1, 1);
				companionRef->ChangeLife(-1.0f);
			}
		}
	}
}

void EnemyProjectile::GiveColliderVelocity(Vector2 velocityBase)
{
	GetCollider()->SetVelocity(velocityBase.x * speed, velocityBase.y * speed);
}

void EnemyProjectile::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));



	if (GetRenderObject()->myTexture->GetTextName() == "graphics/explode64.bmp")
	{
		if (GetRenderObject()->currentColumn >= 5 && GetRenderObject()->currentLine >= 2)
		{
			SetObjectToDestroy();
		}
	}

	++lifeCounter;
	if (lifeCounter == lifetime)
	{
		GetGameEngine()->GetCurrentLevel()->AddObjectToDestroy(this);
	}

}

void EnemyProjectile::Start()
{

}

EnemyProjectile::~EnemyProjectile()
{
	explosionTexture = nullptr;
}
