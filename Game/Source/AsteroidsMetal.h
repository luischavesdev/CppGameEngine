#pragma once
#include "Enemy.h"

class AsteroidsMetal : public Enemy
{
public:
	enum AstSize { Small = 0, Medium, Big };

private:
	float myVelocity;
	int timer = 0;
	int lifetime = 400;
	AstSize mySize;


public:
	AsteroidsMetal(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef, AstSize sizeRef);

	void Start() override;
	void Update() override;

	~AsteroidsMetal();
};