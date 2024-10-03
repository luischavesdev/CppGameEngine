#include <iostream>
#include "AsteroidsStone.h"
#include "Collider.h"
#include "GameEngine.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Texture.h"
#include "Level.h"

AsteroidsStone::AsteroidsStone(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef, 
	AstSize sizeRef, Texture* medAstTextRef, Texture* smlAstTextRef) : Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myVelocity = velRef;
	timer = 0;
	lifetime = 400;
	mySize = sizeRef;
	numOfChildSpawn = 3;
	velocityForSpawn = -1.0f;

	if (medAstTextRef != nullptr)
	{
		mediumAstText = medAstTextRef;
	}

	if (smlAstTextRef != nullptr)
	{
		smallAstText = smlAstTextRef;
	}
}

void AsteroidsStone::SpawnChildren()
{
	switch (mySize)
	{
	case Big:
		textForSpawn = mediumAstText;
		sizeForSpawn = Medium;
		break;

	case Medium:
		textForSpawn = smallAstText;
		sizeForSpawn = Small;
		break;

	case Small:
		sizeForSpawn = Big;
		break;
	}

	if (sizeForSpawn != Big)
	{
		for (int i = 0; i < numOfChildSpawn; ++i)
		{
			spawnColSize[0] = textForSpawn->GetFrameDimensions().width;
			spawnColSize[1] = textForSpawn->GetFrameDimensions().height;
			spawnColPosition[0] = GetLocation().x;
			spawnColPosition[1] = GetLocation().y;

			velocityForSpawn *= -1.0f;


			//Create new Render Obj
			RenderObject* spawnRendObject = new RenderObject(1, 1, textForSpawn, GetGameEngine(), 1.0f, 1, 1);

			//Create new Missile
			AsteroidsStone* spawnObj = new AsteroidsStone("Enemy", spawnRendObject, GetGameEngine(), 1, myVelocity, sizeForSpawn, mediumAstText,
				smallAstText);
			Collider* spawnCol = new Collider(Collider::Dynamic, spawnColPosition, spawnColSize, GetGameEngine()->GetPhysManager(),
				true, spawnObj);

			spawnObj->SetCollider(spawnCol);
			spawnObj->GetCollider()->SetVelocity(myVelocity * (i + 1) * 0.2, (i + 1) * velocityForSpawn * 5.0f);

			GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(spawnObj);
		}
	}

	SetObjectToDestroy();
}

void AsteroidsStone::Die()
{
	isSetToDie = true;
}

void AsteroidsStone::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));

	if (isSetToDie)
	{
		isSetToDie = false;
		SpawnChildren();
	}

	++timer;
	if (timer >= lifetime)
	{
		SetObjectToDestroy();
	}
}

void AsteroidsStone::Start()
{
	GetCollider()->SetVelocity(myVelocity, 0);
}

AsteroidsStone::~AsteroidsStone()
{
	mediumAstText = nullptr;
	smallAstText = nullptr;
	textForSpawn = nullptr;
}
