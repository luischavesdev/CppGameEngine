#pragma once
#include "Enemy.h"	

class AsteroidsStone : public Enemy 
{
public:
	enum AstSize { Small = 0, Medium, Big};

private:
	Vector2 myVelocity;
	int timer = 0;
	int lifetime = 400;
	AstSize mySize;
	bool isSetToDie = false;
	int numOfChildSpawn = 3;

	class Texture* mediumAstText = nullptr;
	Texture* smallAstText = nullptr;

	Vector2 spawnColSize;
	Vector2 spawnColPosition;
	Texture* textForSpawn = nullptr;
	AstSize sizeForSpawn;

	float xVelMltplr = 1.0f;
	float yVelMltplr = 0.0f;


public:
	AsteroidsStone(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, Vector2 velRef, 
		AstSize sizeRef, Texture* medAstTextRef, Texture* smlAstTextRef);

	void Start() override;
	void Update() override;

	void SetVelMultipliers(float x, float y);

	void SpawnChildren();

	void Die() override;

	~AsteroidsStone();
};
