#include <iostream>
#include "AsteroidsMetal.h"
#include "Collider.h"
#include "GameEngine.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Texture.h"

AsteroidsMetal::AsteroidsMetal(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef, 
	AstSize sizeRef) : Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myVelocity = velRef;
	timer = 0;
	lifetime = 400;
	mySize = sizeRef;
}

void AsteroidsMetal::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));


	++timer;
	if (timer >= lifetime)
	{
		SetObjectToDestroy();
	}
}

void AsteroidsMetal::Start()
{
	GetCollider()->SetVelocity(myVelocity, 0);
}

AsteroidsMetal::~AsteroidsMetal()
{

}
