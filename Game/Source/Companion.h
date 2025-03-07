#pragma once
#include "Sprite.h"

class Companion : public Sprite
{
private:
	float missileVelocity = 100.0f;
	float maxLife = 3.0f;
	float life;
	float currentFirepower = 1.0f;
	int missileID = 90;
	int myCompanionRef;
	float shipOffset = 50.0f;

	class Texture* missileTexture = nullptr;
	Texture* explosionTexture = nullptr;
	class Spaceship* mySpaceshipRef = nullptr;

	Vector2 missileColSize;
	Vector2 missileColPosition;


public:
	Companion(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, Texture* missileTextureRef, 
		Texture* altMissileTextureRef, Spaceship* spaceshipRef, int companionRef);

	void Start() override;
	void Update() override;

	void ChangeLife(float lifeToAdd);
	void UpgradeFirepower();
	void UpdateSpawnLocation();

	void SpawnMissile();

	~Companion();
};
