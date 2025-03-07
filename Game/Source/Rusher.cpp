#include "Rusher.h"
#include "Engine.h"
#include "PhysicsManager.h"
#include "Collider.h"

Rusher::Rusher(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef,
	float velRef) : Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myVelocity.x = velRef;
	myVelocity.y = 0;
}

void Rusher::Start()
{
	GetCollider()->SetVelocity(myVelocity.x, myVelocity.y);
}

void Rusher::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));

	++timer;
	if (timer >= lifetime)
	{
		SetObjectToDestroy();
	}
}

void Rusher::Die()
{
	SetObjectToDestroy();
}

Rusher::~Rusher()
{

}
