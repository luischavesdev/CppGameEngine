#include <iostream>
#include "Spawner.h"
#include "RenderObject.h"
#include "Collider.h"
#include "GameEngine.h"
#include "Texture.h"
#include "RenderPipeline.h"
#include "Drone.h"
#include "Level.h"

Spawner::Spawner(std::string objectNameRef, GameEngine* gameEngineRef, int idRef, Texture* textRef, int timeToSpawnRef, Vector2 locationRef) 
	: Object(objectNameRef, gameEngineRef, idRef)
{
	timer = 0;
	timerWave = 0;
	timeIntraWave = 10;
	timeToSpawn = timeToSpawnRef;
	enemyVelocity = 5.0f;
	enemiesByWave = 5; 

	if (textRef != nullptr)
	{
		spawnTypeTexture = textRef;
	}

	SetLocation(locationRef.x, locationRef.y);
	colPosition[0] = GetLocation().x;
	colPosition[1] = GetLocation().y;
	colSize[0] = spawnTypeTexture->GetFrameDimensions().width;
	colSize[1] = spawnTypeTexture->GetFrameDimensions().height;
}

void Spawner::SpawnType()
{
	RenderObject* spawnTypeRendObject = new RenderObject(2, 6, spawnTypeTexture, GetGameEngine(), 1.0f, 1, 1);
	Drone* spawnTypeObject = new Drone("Enemy", spawnTypeRendObject, GetGameEngine(), spawnTypeRendObject->id, enemyVelocity);
	Collider* spawnTypeCol = new Collider(Collider::Dynamic, colPosition, colSize, GetGameEngine()->GetPhysManager(), true, spawnTypeObject);
	spawnTypeObject->SetCollider(spawnTypeCol);
	spawnTypeObject->Start();
	GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(spawnTypeObject);
}

void Spawner::Update()
{
	++timer;
	if (timer >= timeToSpawn)
	{
		++timerWave;
		if (timerWave >= timeIntraWave)
		{
			SpawnType();
			++waveControl;
			timerWave = 0;

			if (waveControl >= enemiesByWave)
			{
				timer = 0;
				waveControl = 0;
			}
		}
	}
}

void Spawner::Start()
{

}

Spawner::~Spawner()
{
	spawnTypeTexture = nullptr;
}
