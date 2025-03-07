#include "Missile.h"
#include "Engine.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Texture.h"
#include "Enemy.h"

Missile::Missile(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, 
	float speedRef, int firepowerRef, Texture* explosionTextRef) : Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	speed = speedRef;
	firepower = firepowerRef;

	if (explosionTextRef != nullptr)
	{
		explosionTexture = explosionTextRef;
	}

	switch (firepower)
	{
	case 1:
		damage = 1;
		break;

	case 2:
		damage = 2;
		break;

	case 3:
		damage = 4;
		break;
	}

	SetRotation(-90.0f);
}

void Missile::Start()
{
	GetCollider()->SetVelocity(speed, 0.0f);
}

void Missile::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));

	if (setToDisable)
	{
		setToDisable = false;
		GetCollider()->SetSensor(true);
	}

	if (!isDisabled)
	{
		if (GetRenderObject()->currentColumn >= 2)
		{
			GetRenderObject()->SkipToFrame(firepower, 1);
		}
	}
	else if (isDisabled)
	{
		if (GetRenderObject()->currentColumn >= 5 && GetRenderObject()->currentLine >= 2)
		{
			SetObjectToDestroy();
		}
	}

	++lifeCounter;

	if (lifeCounter >= lifetime && !isDisabled)
	{
		SetObjectToDestroy();
	}
}

void Missile::OnCollision(Sprite* colliderSpriteRef)
{
	if (colliderSpriteRef != nullptr)
	{
		Enemy* enemyRef = dynamic_cast<Enemy*>(colliderSpriteRef);

		if (enemyRef != nullptr)
		{
			if (isDisabled == false)
			{
				isDisabled = true;
				setToDisable = true;
				GetCollider()->SetVelocity(0, 0);
				GetRenderObject()->ReplaceTexture(explosionTexture, 1, 1);
				enemyRef->ChangeLife(-damage);
			}
		}
		else if (enemyRef != nullptr)
		{
			if (isDisabled == false)
			{
				isDisabled = true;
				SetObjectToDestroy();
			}
		}
	}
}

Missile::~Missile()
{
	explosionTexture = nullptr;
}
