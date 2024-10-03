#include <iostream>
#include "Rusher.h"
#include "Collider.h"
#include "GameEngine.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Texture.h"

Rusher::Rusher(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef,
	float velRef) : Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myVelocity.x = velRef;
	myVelocity.y = 0;
	timer = 0;
	lifetime = 200;
}

void Rusher::Die()
{
	SetObjectToDestroy();
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

void Rusher::Start()
{
	GetCollider()->SetVelocity(myVelocity.x, myVelocity.y);
}

Rusher::~Rusher()
{

}