#pragma once
#include "Sprite.h"

class Enemy : public Sprite 
{
private:
	float damageVal = 10.0f;
	float life;
	float maxLife = 3.0f;
	float scoreWorth = 10.0f;


public:
	Enemy(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef);

	void Start() override;
	void Update() override;

	void OnCollision(Sprite* colliderSpriteRef) override;

	inline int GetDamage() { return damageVal; };
	void ChangeLife(float lifeToAdd);

	virtual void Die();

	~Enemy();
};
