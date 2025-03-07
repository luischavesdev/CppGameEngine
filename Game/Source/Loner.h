#pragma once
#include "Enemy.h"

class Loner : public Enemy
{
private:
	float velocity;
	float projectileVelocity = 80.0f;
	int spawnTimer = 0;
	int timeToSpawn = 50;

	Vector2 spawnLocation;
	class Texture* projectileTexture = nullptr;
	Texture* altProjectileTexture = nullptr;

	class Spaceship* mySpaceshipRef = nullptr;
	Vector2 projDir;
	float projDirMagn = 0;

	Vector2 projectileColSize;
	Vector2 projectileColPosition;

	int projectileID = 50;


public:
	Loner(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velocityRef,
		Texture* projTextureRef, Texture* altProjTextureRef, Spaceship* spaceshipRef);

	void Start() override;
	void Update() override;

	void UpdateProjectileData();
	void SpawnProjectile();

	void Die() override;

	~Loner();
};
