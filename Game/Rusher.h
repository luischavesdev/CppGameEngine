#pragma once
#include "Enemy.h"
#include "Vector2.h"
#include <string>

class Rusher : public Enemy
{
private:
	Vector2 myVelocity;
	int timer;
	int lifetime;

public:
	Rusher(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef);

	void Die() override;

	void Update() override;

	void Start() override;

	~Rusher();
};