#include "Enemy.h"
#include "Engine.h"
#include "Spaceship.h"
#include "Companion.h"
#include "AudioManager.h"

Enemy::Enemy(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef) : 
	Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	life = maxLife;
}

void Enemy::Start()
{

}

void Enemy::Update()
{

}

void Enemy::OnCollision(Sprite* colliderSpriteRef)
{
	if (colliderSpriteRef != nullptr)
	{
		Spaceship* spaceshipRef = dynamic_cast<Spaceship*>(colliderSpriteRef);
		if (spaceshipRef != nullptr)
		{
			spaceshipRef->ChangeLife(-damageVal);
			SetObjectToDestroy();
		}
		else
		{
			Companion* companionRef = dynamic_cast<Companion*>(colliderSpriteRef);
			if (companionRef != nullptr)
			{
				companionRef->ChangeLife(-damageVal);
				SetObjectToDestroy();
			}
		}
	}
}

void Enemy::ChangeLife(float lifeToAdd)
{
	life = std::max(0.0f, std::min(life + lifeToAdd, maxLife));

	if (life <= 0.0f)
	{
		GetGameEngine()->GetAudioManager()->PlaySound(0, "data/audio/EnemyExplosion.wav", 60);
		Die();
	}
	else
	{
		GetGameEngine()->GetAudioManager()->PlaySound(0, "data/audio/MetallicHit.wav", 30);
	}
}

void Enemy::Die()
{

}

Enemy::~Enemy()
{

}
