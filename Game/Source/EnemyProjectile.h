#pragma once
#include "Sprite.h"

class EnemyProjectile : public Sprite
{
private:
	float speed;
	float lifeCounter = 0;
	float lifetime = 50.0f;
	class Texture* explosionTexture = nullptr;
	bool exploding = false;


public:
	EnemyProjectile(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float speedRef, 
		Texture* explosionTextRef);

	void Start() override;
	void Update() override;

	void OnCollision(Sprite* colliderSpriteRef) override;

	void GiveColliderVelocity(Vector2 baseVelocity);

	~EnemyProjectile();
};
