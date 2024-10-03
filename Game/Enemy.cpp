#include <iostream>
#include "Enemy.h"
#include "Collider.h"
#include "GameEngine.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Texture.h"
#include "Spaceship.h"
#include "Companion.h"
#include "GameState.h"
#include "AudioManager.h"


Enemy::Enemy(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef) : 
	Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	maxLife = 3.0f;
	life = maxLife;
	damageVal = 10.0f;
	scoreWorth = 10.0f;
}

void Enemy::ChangeLife(float lifeToAdd)
{
	life = std::max(0.0f, std::min(life + lifeToAdd, maxLife));

	if (life <= 0.0f)
	{
		GetGameEngine()->GetGameState()->ChangeScore(scoreWorth);

		GetGameEngine()->myAudioManager->PlaySound(0, "audio/EnemyExplosion.wav", 60);
		Die();
	}
	else
	{
		GetGameEngine()->myAudioManager->PlaySound(0, "audio/MetallicHit.wav", 30);
	}
}

void Enemy::OnCollision(Sprite* colliderSpriteRef)
{
	if (colliderSpriteRef != nullptr)
	{
		Spaceship* spaceshipRef = static_cast<Spaceship*>(colliderSpriteRef);
		if (spaceshipRef->GetName() == "Spaceship")
		{
			spaceshipRef->ChangeLife(-damageVal);
			SetObjectToDestroy();
		}
		else 
		{
			Companion* companionRef = static_cast<Companion*>(colliderSpriteRef);
			if (companionRef->GetName() == "Companion")
			{
				companionRef->ChangeLife(-damageVal);
				SetObjectToDestroy();
			}
		}
	}
}

void Enemy::Die()
{

}

void Enemy::Update()
{

}

void Enemy::Start()
{

}

Enemy::~Enemy()
{

}
