#include "Spawner.h"
#include "Engine.h"
#include "Texture.h"
#include "Level.h"
#include "Drone.h"
#include "Collider.h"
#include "RenderObject.h"

Spawner::Spawner(std::string objectNameRef, GameEngine* gameEngineRef, int idRef, Texture* textRef, int timeToSpawnRef, Vector2 locationRef) 
	: Object(objectNameRef, gameEngineRef, idRef)
{
	timeToSpawn = timeToSpawnRef;

	if (textRef != nullptr)
	{
		spawnTypeTexture = textRef;
	}

	SetLocation(locationRef.x, locationRef.y);
	colPosition.x = GetLocation().x;
	colPosition.y = GetLocation().y;
	colSize.x = spawnTypeTexture->GetFrameDimensions().width;
	colSize.y = spawnTypeTexture->GetFrameDimensions().height;
}

void Spawner::Start()
{

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

void Spawner::SpawnType()
{ 
	RenderObject* spawnTypeRendObject = new RenderObject(2, 6, spawnTypeTexture, GetGameEngine(), 1.0f, 1, 1);
	Drone* spawnTypeObject = new Drone("Enemy", spawnTypeRendObject, GetGameEngine(), spawnTypeRendObject->id, enemyVelocity);
	Collider* spawnTypeCol = new Collider(Collider::Dynamic, colPosition, colSize, GetGameEngine()->GetPhysManager(), true, spawnTypeObject);
	spawnTypeObject->SetCollider(spawnTypeCol);
	GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(spawnTypeObject);
}

Spawner::~Spawner()
{
	spawnTypeTexture = nullptr;
}
