#pragma once
#include "Enemy.h"
#include <string>

class AsteroidsMetal : public Enemy
{
public:
	enum AstSize { Small = 0, Medium, Big };

private:
	float myVelocity;
	int timer;
	int lifetime;
	AstSize mySize;

public:
	AsteroidsMetal(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef, AstSize sizeRef);

	void Update() override;

	void Start() override;

	~AsteroidsMetal();
};