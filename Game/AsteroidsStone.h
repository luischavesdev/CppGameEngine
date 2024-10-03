#pragma once
#include "Enemy.h"	
#include <string>

class AsteroidsStone : public Enemy 
{
public:
	enum AstSize { Small = 0, Medium, Big};

private:
	float myVelocity;
	int timer;
	int lifetime;
	AstSize mySize;
	bool isSetToDie = false;
	int numOfChildSpawn;
	float velocityForSpawn;

	class Texture* mediumAstText;
	Texture* smallAstText;

	float spawnColSize[2];
	float spawnColPosition[2];
	Texture* textForSpawn;
	AstSize sizeForSpawn;

public:
	AsteroidsStone(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef, AstSize sizeRef, 
		Texture* medAstTextRef, Texture* smlAstTextRef);

	void SpawnChildren();

	void Die() override;

	void Update() override;

	void Start() override;

	~AsteroidsStone();
};