#pragma once
#include "Sprite.h"
#include <string>
#include <vector>

class Companion : public Sprite
{
public:
	struct SpawnLocation
	{
		int xPos;
		int yPos;
	};

private:
	float missileVelocity;
	float maxLife;
	float life;
	float currentFirepower;
	int missileID = 90;
	int myCompanionRef;
	float shipOffset;

	SpawnLocation mySpawnLocation;
	class Texture* missileTexture;
	Texture* explosionTexture;
	class Spaceship* mySpaceshipRef = nullptr;


	float missileColSize[2];
	float missileColPosition[2];



public:
	Companion(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, Texture* missileTextureRef, 
		Texture* altMissileTextureRef, Spaceship* spaceshipRef, int companionRef);

	SpawnLocation GetMySpawnLocation();

	void UpdateProjectileData();

	void SpawnMissile();

	void ChangeLife(float lifeToAdd);

	void UpgradeFirepower();

	void Update() override;

	void Start() override;

	~Companion();
};
