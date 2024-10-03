#pragma once
#include "Sprite.h"
#include <string>

class Enemy : public Sprite 
{
private:
	float damageVal;
	float life;
	float maxLife;
	float scoreWorth;

public:
	Enemy(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef);

	inline int GetDamage() { return damageVal; };

	void ChangeLife(float lifeToAdd);

	void OnCollision(Sprite* colliderSpriteRef) override;

	virtual void Die();

	void Update() override;

	void Start() override;

	~Enemy();
};