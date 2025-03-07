#include "AsteroidsStone.h"
#include "Engine.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Texture.h"
#include "Level.h"

AsteroidsStone::AsteroidsStone(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, Vector2 velRef, 
	AstSize sizeRef, Texture* medAstTextRef, Texture* smlAstTextRef) : Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myVelocity = velRef;
	mySize = sizeRef;

	if (medAstTextRef != nullptr)
	{
		mediumAstText = medAstTextRef;
	}

	if (smlAstTextRef != nullptr)
	{
		smallAstText = smlAstTextRef;
	}
}

void AsteroidsStone::Start()
{
	GetCollider()->SetVelocity(myVelocity.x * xVelMltplr, myVelocity.y * yVelMltplr);
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

void AsteroidsStone::SetVelMultipliers(float x, float y)
{
	xVelMltplr = x;
	yVelMltplr = y;
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
		// Used to alternate vertical direction of child asteroids
		float toggle = 1.0f;

		for (int i = 0; i < numOfChildSpawn; ++i)
		{
			spawnColSize.x = textForSpawn->GetFrameDimensions().width;
			spawnColSize.y = textForSpawn->GetFrameDimensions().height;
			spawnColPosition.x = GetLocation().x;
			spawnColPosition.y = GetLocation().y;


			RenderObject* spawnRendObject = new RenderObject(1, 1, textForSpawn, GetGameEngine(), 1.0f, 1, 1);
			AsteroidsStone* spawnObj = new AsteroidsStone("Enemy", spawnRendObject, GetGameEngine(), 1, myVelocity, sizeForSpawn, mediumAstText,
				smallAstText);
			Collider* spawnCol = new Collider(Collider::Dynamic, spawnColPosition, spawnColSize, GetGameEngine()->GetPhysManager(),
				true, spawnObj);

			spawnObj->SetCollider(spawnCol);
			toggle *= -1.0f;
			spawnObj->SetVelMultipliers((i + 1) * 0.1, (i + 1) * 5.0f * toggle);

			GetGameEngine()->GetCurrentLevel()->AddObjectToBuffer(spawnObj);
		}
	}

	SetObjectToDestroy();
}

void AsteroidsStone::Die()
{
	isSetToDie = true;
}

AsteroidsStone::~AsteroidsStone()
{
	mediumAstText = nullptr;
	smallAstText = nullptr;
	textForSpawn = nullptr;
}
