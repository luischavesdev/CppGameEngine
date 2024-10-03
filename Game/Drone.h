#pragma once
#include "Enemy.h"
#include "Vector2.h"
#include <string>

class Drone : public Enemy 
{
private:
	float myVelocity;
	float timer;
	float lifeTime;

public:
	Drone(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef);

	void Die() override;

	void Update() override;

	void Start() override;

	~Drone();
};