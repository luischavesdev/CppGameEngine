#include "AsteroidsMetal.h"
#include "Engine.h"
#include "PhysicsManager.h"
#include "Collider.h"

AsteroidsMetal::AsteroidsMetal(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef, 
	AstSize sizeRef) : Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myVelocity = velRef;
	mySize = sizeRef;
}

void AsteroidsMetal::Start()
{
	GetCollider()->SetVelocity(myVelocity, 0);
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

AsteroidsMetal::~AsteroidsMetal()
{

}
