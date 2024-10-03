#pragma once
#include "Sprite.h"
#include <string>
#include "Vector2.h"

class EnemyProjectile : public Sprite
{
private:
	float speed;
	float lifeCounter;
	float lifetime;
	class Texture* explosionTexture = nullptr;

public:

	EnemyProjectile(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float speedRef, 
		Texture* explosionTextRef);

	void OnCollision(Sprite* colliderSpriteRef) override;

	void GiveColliderVelocity(Vector2 baseVelocity);

	void Update() override;

	void Start() override;

	~EnemyProjectile();
};