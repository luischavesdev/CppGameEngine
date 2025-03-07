#pragma once
#include "Enemy.h"

class Drone : public Enemy 
{
private:
	float myVelocity;
	float timer = 0;
	float lifeTime = 20.0f;


public:
	Drone(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef);

	void Start() override;
	void Update() override;

	void Die() override;

	~Drone();
};
