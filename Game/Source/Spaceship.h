#pragma once
#include <vector>
#include "Pawn.h"

class Spaceship : public Pawn 
{
private:
	float velocity;
	float missileVelocity = 100.0f;
	float maxLife = 8.0f;
	float life;
	int extraLives = 2;
	float currentFirepower = 1.0f;
	int companionManager[2];
	bool canSpawnCompanion = false;

	Vector2 mySpawnLocation;
	Vector2 inputVector;

	class Texture* missileTexture = nullptr;
	Texture* explosionTexture = nullptr;
	Texture* companionTexture = nullptr;
	class Companion* myCompanionRef0 = nullptr;
	Companion* myCompanionRef1 = nullptr;

	Vector2 missileColSize;
	Vector2 missileColPosition;

	int missileID = 10;
	
	std::vector<Spaceship**> spaceshipRefs{};

	void UpdateInputVector();


public:
	Spaceship(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velocityRef, Texture* missileTextureRef, 
		Texture* altMissileTextureRef, Texture* companionTextRef);

	void Start() override;
	void Update() override;
	
	inline float GetLife() { return life; };
	inline float GetExtraLives() { return extraLives; };

	void UpdateProjectileData();
	void SpawnMissile();
	void SpawnCompanion();
	void UpgradeFirepower();
	void ChangeLife(float lifeToAdd);
	void AddCompanion();
	void UpdateCompanionStatus(int companionRef, bool trueFalse);
	void AddSpaceshipRef(Spaceship** pointer);

	~Spaceship();
};
