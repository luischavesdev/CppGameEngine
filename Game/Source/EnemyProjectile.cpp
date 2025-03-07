#include "EnemyProjectile.h"
#include "Engine.h"
#include "Level.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Texture.h"
#include "Spaceship.h"
#include "Companion.h"

EnemyProjectile::EnemyProjectile(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef,
	float speedRef, Texture* explosionTextRef) : Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	speed = speedRef;

	if (explosionTextRef != nullptr)
	{
		explosionTexture = explosionTextRef;
	}
}

void EnemyProjectile::Start()
{

}

void EnemyProjectile::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));

	if (exploding)
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

void EnemyProjectile::OnCollision(Sprite* colliderSpriteRef)
{
	if (colliderSpriteRef != nullptr)
	{
		Spaceship* spaceshipRef = dynamic_cast<Spaceship*>(colliderSpriteRef);
		if (spaceshipRef != nullptr)
		{
			GetCollider()->SetVelocity(0, 0);
			GetRenderObject()->ReplaceTexture(explosionTexture, 1, 1);
			spaceshipRef->ChangeLife(-1.0f);
			exploding = true;
		}
		else
		{
			Companion* companionRef = dynamic_cast<Companion*>(colliderSpriteRef);
			if (companionRef != nullptr)
			{
				GetCollider()->SetVelocity(0, 0);
				GetRenderObject()->ReplaceTexture(explosionTexture, 1, 1);
				companionRef->ChangeLife(-1.0f);
				exploding = true;
			}
		}
	}
}

void EnemyProjectile::GiveColliderVelocity(Vector2 velocityBase)
{
	GetCollider()->SetVelocity(velocityBase.x * speed, velocityBase.y * speed);
}

EnemyProjectile::~EnemyProjectile()
{
	explosionTexture = nullptr;
}
