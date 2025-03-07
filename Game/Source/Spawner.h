#pragma once
#include "Object.h"

class Spawner : public Object 
{
private:
	int timer = 0;
	int timerWave = 0;
	int timeIntraWave = 10;
	int timeToSpawn;
	int waveControl = 0;

	float enemyVelocity = 5.0f;
	int enemiesByWave = 5;

	//Spawn Type Vars
	class Texture* spawnTypeTexture = nullptr;
	Vector2 colPosition;
	Vector2 colSize;


public:
	Spawner(std::string objectNameRef, class GameEngine* gameEngineRef, int idRef, Texture* textRef, int timeToSpawnRef, Vector2 locationRef);

	void Start() override;
	void Update() override;

	void SpawnType();

	~Spawner();
};
