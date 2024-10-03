#pragma once
#include "Enemy.h"
#include "Vector2.h"
#include <string>

class Loner : public Enemy
{
private:
	float velocity;
	float projectileVelocity;
	int spawnTimer;
	int timeToSpawn;

	Vector2 spawnLocation;
	class Texture* projectileTexture;
	Texture* altProjectileTexture;

	class Spaceship* mySpaceshipRef = nullptr;
	Vector2 projDir;
	float projDirMagn;

	float projectileColSize[2];
	float projectileColPosition[2];

	int projectileID = 50;

public:
	Loner(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velocityRef, 
		Texture* projTextureRef, Texture* altProjTextureRef, Spaceship* spaceshipRef);

	Vector2 GetMySpawnLocation();

	void UpdateProjectileData();

	void SpawnProjectile();

	void Die() override;

	void Update() override;

	void Start() override;

	~Loner();
};