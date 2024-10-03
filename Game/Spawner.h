#pragma once
#include <string>
#include "Object.h"
#include "Vector2.h"


class Spawner : public Object 
{
private:
	int timer;
	int timerWave;
	int timeIntraWave;
	int timeToSpawn;
	int waveControl;
	float enemyVelocity;
	int enemiesByWave;

	//Spawn Type Vars
	class Texture* spawnTypeTexture;
	float colPosition[2];
	float colSize[2];

public:
	Spawner(std::string objectNameRef, GameEngine* gameEngineRef, int idRef, Texture* textRef, int timeToSpawnRef, Vector2 locationRef);

	void SpawnType();

	void Update() override;

	void Start() override;

	~Spawner();
};