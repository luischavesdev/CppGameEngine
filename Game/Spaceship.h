#pragma once
#include "Pawn.h"
#include <string>
#include <vector>

class Spaceship : public Pawn 
{
public:
	struct SpawnLocation 
	{
		int xPos;
		int yPos;
	};

private:
	float velocity;
	float missileVelocity;
	float maxLife;
	float life;
	int extraLives;
	float currentFirepower;
	int companionManager[2];
	bool canSpawnCompanion = false;

	SpawnLocation mySpawnLocation;

	class Texture* missileTexture;
	Texture* explosionTexture;
	Texture* companionTexture;
	class Companion* myCompanionRef0 = nullptr;
	Companion* myCompanionRef1 = nullptr;


	float missileColSize[2];
	float missileColPosition[2];

	int missileID = 10;

	int compMissileTimer = 0;
	

public:
	Spaceship(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velocityRef, Texture* missileTextureRef, 
		Texture* altMissileTextureRef, Texture* companionTextRef);

	Vector2 getInputVector();

	SpawnLocation GetMySpawnLocation();

	void UpdateProjectileData();

	void SpawnMissile();

	void SpawnCompanion();

	void ChangeLife(float lifeToAdd);

	inline float GetLife() { return life; };

	inline float GetExtraLives() { return extraLives; };

	void UpgradeFirepower();

	void AddCompanion();

	void UpdateCompanionStatus(int companionRef, bool trueFalse);

	void Update() override;

	void Start() override;

	~Spaceship();
};