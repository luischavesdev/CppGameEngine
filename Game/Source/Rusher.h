#pragma once
#include "Enemy.h"

class Rusher : public Enemy
{
private:
	Vector2 myVelocity;
	int timer = 0;
	int lifetime = 200;

public:
	Rusher(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef);

	void Start() override;
	void Update() override;

	void Die() override;

	~Rusher();
};
